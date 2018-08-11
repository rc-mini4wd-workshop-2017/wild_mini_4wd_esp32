// Copyright 2018 Quattro Ace. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#pragma once

#include <string>

class Stream;
class Command;
class CommandLineParser;

class CommandLine {
public:
    CommandLine();

public:
    void Initialize(Stream *stream);
    bool AddCommand(Command *command);
    bool Analyze();

private:
    bool analyzeSerial();
    bool analyzeStream();
    void analyzeChar(char ch);
    int executeCommandLine(const char *line);

private:
    enum {
        kCommandCapacity = 16
    };
    Command *commands[kCommandCapacity];
    int commandSize;
    std::string  buf;
    Stream *stream;
};
