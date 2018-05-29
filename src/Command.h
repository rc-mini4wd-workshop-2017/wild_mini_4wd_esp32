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

protected:
    Stream *stream;
};
