// Copyright 2018 Quattro Ace. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

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
    boolean analyzeSerial();
    boolean analyzeStream();
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
