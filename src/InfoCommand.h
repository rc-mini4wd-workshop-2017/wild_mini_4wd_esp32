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
        reply("version=");
        reply(VERSION);
        reply("\n");
        return 0;
    }
};
