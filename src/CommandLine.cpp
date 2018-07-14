
#include "CommandLine.h"
#include "Version.h"
#include "Log.h"
#include "Command.h"
#include "CommandLineParser.h"

CommandLine::CommandLine()
{
}

void CommandLine::Initialize(Stream *stream)
{
    this->stream = stream;
    buf = "";
}

boolean CommandLine::AddCommand(Command *command)
{
    if (commandSize >= kCommandCapacity) {
        return false;
    }
    commands[commandSize] = command;
    ++commandSize;
}

boolean CommandLine::Analyze()
{
    boolean bSerialResult = analyzeSerial();
    boolean bStreamResult = analyzeStream();
    return bSerialResult || bStreamResult;
}

boolean CommandLine::analyzeSerial()
{
    if (!Serial.available()) {
        return false;
    }

    while (Serial.available()) {
        char ch = Serial.read();
        analyzeChar(ch);
    }
    return true;
}

boolean CommandLine::analyzeStream()
{
    if (!stream->available()) {
        return false;
    }

    while (stream->available()) {
        char ch = stream->read();
        analyzeChar(ch);
    }
    return true;
}

void CommandLine::analyzeChar(char ch)
{
    if (ch == '\r') {
        return;
    }
    Serial.write(ch);
    stream->write(ch);

    switch (ch) {
    case '\n':
        if (buf.length() != 0) {
            int result = executeCommandLine(buf.c_str());
            Serial.write("\nresult: ");
            Serial.print(result);
            Serial.write("\n\n");
            stream->write("\nresult: ");
            stream->print(result);
            stream->write("\n\n");
        }
        buf = "";
        break;
    default:
        buf.concat(ch);
        break;
    }
}

int CommandLine::executeCommandLine(const char *line)
{
    Log::Info(line);
    CommandLineParser parser(line);
    if (!parser.Parse()) {
        Log::Error("parser: buffer over error");
        return 1;
    }

    for (int i=0; i<commandSize; i++) {
        Command* command = commands[i];
        if (strcmp(parser.GetName(), command->GetName()) == 0) {
            int result = command->Execute(&parser);
            String log = command->GetName();
            log += ": returns ";
            log += result;
            Log::Trace(log.c_str());
            return result;
        }
    }
    Log::Error("parser: unknown command");
    return 2;
}

