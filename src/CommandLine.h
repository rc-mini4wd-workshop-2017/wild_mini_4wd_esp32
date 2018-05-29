#pragma once

#include "Arduino.h"
#include "Stream.h"

class Command;
class CommandLineParser;

class CommandLine {
public:
    CommandLine();

public:
    void Initialize(Stream *stream);
    boolean AddCommand(Command *command);
    boolean Analyze();

private:
    void analyzeChar(char ch);
    int executeCommandLine(const char *line);

private:
    enum {
        kCommandCapacity = 16
    };
    Command *commands[kCommandCapacity];
    int commandSize;
    String  buf;
    Stream *stream;
};
