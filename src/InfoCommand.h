#pragma once

#include "Command.h"
#include "Version.h"

class InfoCommand : public Command {
public:
    InfoCommand() {}
    ~InfoCommand() {}

public:
    const char *GetName() {
        return "info";
    }

    int Execute(const CommandLineParser *parser) {
        Serial.write("version=");
        Serial.print(VERSION);
        Serial.write("\n");
        stream->write("version=");
        stream->write(VERSION);
        stream->write("\n");
        return 0;
    }
};
