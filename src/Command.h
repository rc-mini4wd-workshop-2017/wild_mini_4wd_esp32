// Copyright 2018 Quattro Ace. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#pragma once

#include "CommandLineParser.h"

class Stream;

class Command {
public:
    Command(){};
    virtual ~Command(){};

public:
    virtual void Initialize(Stream *stream) {
        this->stream = stream;
    }
    virtual const char *GetName() = 0;
    virtual int Execute(const CommandLineParser *parser) = 0;
    void reply(char ch) {
        Serial.write(ch);
        stream->write(ch);
    }
    void reply(int i) {
        Serial.write(i);
        stream->write(i);
    }
    void reply(const char *str) {
        Serial.write(str);
        stream->write(str);
    }

protected:
    Stream *stream;
};
