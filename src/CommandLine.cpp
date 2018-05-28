
#include <Servo.h>
#include <Wire.h>
#include "CommandLine.h"
#include "Version.h"
#include "Log.h"
#include "CommandLineParser.h"

const int I2C_SDA = 21;
const int I2C_SCL = 22;

const int RV8830_WRITE_ADDRESS = 0x64; // 0xc8 >> 1
const int RV8830_READ_ADDRESS  = 0x64; // 0xc9 >> 1
const int RV8830_CONTROL       = 0;

CommandLine::CommandLine()
{
}

void CommandLine::Initialize(Stream *stream)
{
    this->stream = stream;
    pinMode(I2C_SDA, INPUT_PULLUP);
    pinMode(I2C_SCL, INPUT_PULLUP);
    Wire.begin();
    Wire.setClock(10000);
    buf = "";
}

boolean CommandLine::Analyze()
{
    if (!stream->available()) {
        return false;
    }

    char ch = stream->read();
    analyzeChar(ch);
    return true;
}

void CommandLine::analyzeChar(char ch)
{
    if (ch == '\r') {
        return;
    }
    writeChar(ch);

    switch (ch) {
    case '\n':
        if (buf.length() != 0) {
            executeCommandLine(buf.c_str());
        }
        buf = "";
        writeMessage("\n");
        break;
    default:
        buf.concat(ch);
        break;
    }
}

size_t CommandLine::writeMessage(const char *message)
{
    Serial.print(message);
    int length = strlen(message);
    return stream->write((uint8_t*)message, length);
}

size_t CommandLine::writeChar(char ch)
{
    Serial.write(ch);
    return stream->write(ch);
}

void CommandLine::writeError(const char *message)
{
    Log::Error(message);
    writeMessage(message);
    writeMessage("\n");
}

void CommandLine::writeInfo(const char *message)
{
    Log::Info(message);
    writeMessage(message);
    writeMessage("\n");
}

bool CommandLine::executeLogCommand(const CommandLineParser *parser)
{
    for (int i=0; i<Log::LOG_CAPACITY; i++) {
        String log;
        if (!Log::GetLog(i, log)) {
            return true;
        }
        writeMessage(log.c_str());
        writeMessage("\n");
    }
    return true;
}

bool CommandLine::executeSetLogLevelCommand(const CommandLineParser *parser)
{
    const char *level = parser->GetFirstArg();
    if (level == 0) {
        writeError("set_loglevel: no log level");
        return false;
    }
    if (strcmp(level, "TRACE") == 0) {
        writeInfo("set_loglevel: set TRACE");
        Log::SetLevel(Log::LOG_LEVEL_TRACE);
        return true;
    }
    if (strcmp(level, "DEBUG") == 0) {
        writeInfo("set_loglevel: set DEBUG");
        Log::SetLevel(Log::LOG_LEVEL_DEBUG);
        return true;
    }
    if (strcmp(level, "INFO") == 0) {
        writeInfo("set_loglevel: set INFO");
        Log::SetLevel(Log::LOG_LEVEL_INFO);
        return true;
    }
    if (strcmp(level, "WARN") == 0) {
        writeInfo("set_loglevel: set WARN");
        Log::SetLevel(Log::LOG_LEVEL_WARN);
        return true;
    }
    if (strcmp(level, "ERROR") == 0) {
        writeInfo("set_loglevel: set ERROR");
        Log::SetLevel(Log::LOG_LEVEL_ERROR);
        return true;
    }
    if (strcmp(level, "FATAL") == 0) {
        writeInfo("set_loglevel: set FATAL");
        Log::SetLevel(Log::LOG_LEVEL_FATAL);
        return true;
    }
    writeError("set_loglevel: unknown level");
    return false;
}

bool CommandLine::executeSetDigitalCommand(const CommandLineParser *parser)
{
    const char *arg = parser->GetFirstArg();
    if (arg == 0) {
        writeError("set_digital: invalid index");
        return false;
    }
    int pin = atoi(arg);

    const char *state = parser->NextArg(arg);
    if (strcmp(state, "HIGH") == 0) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH);
        return true;
    }
    if (strcmp(state, "LOW") == 0) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
        return true;
    }

    writeError("set_digital: unknown level");
    return false;
}

bool CommandLine::executeSetServoCommand(const CommandLineParser *parser)
{
    const char *arg = parser->GetFirstArg();
    if (arg == 0) {
        writeError("set_servo: invalid index");
        return false;
    }
    int pin = atoi(arg);

    arg = parser->NextArg(arg);
    if (arg == 0) {
        writeError("set_servo: invalid angle");
        return false;
    }
    int degrees = atoi(arg);

    Servo servo;
    servo.attach(pin);
    servo.write(degrees);
    vTaskDelay(200);
    servo.detach();

    return true;
}

bool CommandLine::executeSetMotorCommand(const CommandLineParser *parser)
{
    const char *arg = parser->GetFirstArg();
    if (arg == 0) {
        writeError("set_motor: invalid control value");
        return false;
    }
    int control = atoi(arg);

    for (int i=0; i<10; i++) {
        Wire.beginTransmission(RV8830_WRITE_ADDRESS);
        Wire.write(RV8830_CONTROL);
        Wire.write(control);

        int result = Wire.endTransmission();
        switch (result) {
        case 0: writeInfo("set_motor: success");                          return true;
        case 1: writeError("set_motor: buffer overflow error");           return false;
        case 2: writeError("set_motor: slave addr: nack received error"); return false;
        case 3: writeError("set_motor: data: nack received error");       return false;
        case 4: writeError("set_motor: error");                           return false;
        }
        // workaround for esp-32 i2c bug
        // see http://d.hatena.ne.jp/wakwak_koba/20171228
        // see https://github.com/espressif/arduino-esp32/issues/349
        Wire.reset();
        writeError("set_motor: unknown result error");
    }

    return false;
}

bool CommandLine::executeInfoCommand(const CommandLineParser *parser)
{
    writeMessage("version=");
    writeMessage(VERSION);
    return true;
}

bool CommandLine::executeCommandLine(const char *line)
{
    CommandLineParser parser(line);
    if (!parser.Parse()) {
        return false;
    }

    if (strcmp(parser.GetName(), "log") == 0) {
        return executeLogCommand(&parser);
    }
    if (strcmp(parser.GetName(), "set_loglevel") == 0) {
        return executeSetLogLevelCommand(&parser);
    }
    if (strcmp(parser.GetName(), "info") == 0) {
        return executeInfoCommand(&parser);
    }
    if (strcmp(parser.GetName(), "set_digital") == 0) {
        return executeSetDigitalCommand(&parser);
    }
    if (strcmp(parser.GetName(), "set_servo") == 0) {
        return executeSetServoCommand(&parser);
    }
    if (strcmp(parser.GetName(), "set_motor") == 0) {
        return executeSetMotorCommand(&parser);
    }
    writeError("parser: unknown command");
    return true;
}

