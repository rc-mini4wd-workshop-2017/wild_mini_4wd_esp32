#pragma once

#include "Command.h"

class LogCommand : public Command {
public:
    LogCommand() {}
    ~LogCommand() {}

public:
    const char *GetName() {
        return "log";
    }

    int Execute(const CommandLineParser *parser) {
        for (int i=0; i<Log::LOG_CAPACITY; i++) {
            String log;
            if (!Log::GetLog(i, log)) {
                return 0;
            }
            stream->write(log.c_str());
            stream->write("\n");
        }
        return 0;
    }
};
