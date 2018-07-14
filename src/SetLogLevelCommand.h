#pragma once

#include "Command.h"

class SetLogLevelCommand : public Command {
public:
    SetLogLevelCommand() {}
    ~SetLogLevelCommand() {}

public:
    const char *GetName() {
        return "set_loglevel";
    }

    int Execute(const CommandLineParser *parser) {
        const char *level = parser->GetFirstArg();
        if (level == 0) {
            Log::Error("set_loglevel: no log level");
            return 2;
        }

        if (strcmp(level, "TRACE") == 0) {
            Log::Info("set_loglevel: set TRACE");
            Log::SetLevel(Log::LOG_LEVEL_TRACE);
            return 0;
        } else if (strcmp(level, "DEBUG") == 0) {
            Log::Info("set_loglevel: set DEBUG");
            Log::SetLevel(Log::LOG_LEVEL_DEBUG);
            return 0;
        } else if (strcmp(level, "INFO") == 0) {
            Log::Info("set_loglevel: set INFO");
            Log::SetLevel(Log::LOG_LEVEL_INFO);
            return 0;
        } else if (strcmp(level, "WARN") == 0) {
            Log::Info("set_loglevel: set WARN");
            Log::SetLevel(Log::LOG_LEVEL_WARN);
            return 0;
        } else if (strcmp(level, "ERROR") == 0) {
            Log::Info("set_loglevel: set ERROR");
            Log::SetLevel(Log::LOG_LEVEL_ERROR);
            return 0;
        } else if (strcmp(level, "FATAL") == 0) {
            Log::Info("set_loglevel: set FATAL");
            Log::SetLevel(Log::LOG_LEVEL_FATAL);
            return 0;
        }
        Log::Error("set_loglevel: unknown level");
        return 1;
    }
};
