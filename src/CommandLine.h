#pragma once

#include "Arduino.h"
#include "Stream.h"

class CommandLineParser;

class CommandLine {
public:
    CommandLine();

public:
    void Initialize(Stream *stream);
    boolean Analyze();
    void Write(char ch);

private:
    size_t writeMessage(const char *message);
    size_t writeChar(char ch);
    void writeError(const char *message);
    void writeInfo(const char *message);
    bool executeLogCommand(const CommandLineParser *parser);
    bool executeSetLogLevelCommand(const CommandLineParser *parser);
    bool executeInfoCommand(const CommandLineParser *parser);
    bool executeSetDigitalCommand(const CommandLineParser *parser);
    bool executeSetServoCommand(const CommandLineParser *parser);
    bool executeCommandLine(const char *line);

private:
    String  buf;
    Stream *stream;
};
