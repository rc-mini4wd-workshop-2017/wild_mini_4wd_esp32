// Copyright 2018 Quattro Ace. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#pragma once

#include "command/Command.h"

class SetDigitalCommand : public Command {
public:
    SetDigitalCommand() {}
    ~SetDigitalCommand() {}

public:
    const char *GetName() {
        return "set_digital";
    }

    int Execute(const CommandLineParser *parser) {
        const char *arg = parser->GetFirstArg();
        if (arg == 0) {
            Log::Error("set_digital: invalid index");
            return 1;
        }
        int pin = atoi(arg);

        const char *state = parser->NextArg(arg);
        if (strcmp(state, "HIGH") == 0) {
            Log::Trace("set_digital: HIGH");
            pinMode(pin, OUTPUT);
            digitalWrite(pin, HIGH);
            return 0;
        } else if (strcmp(state, "LOW") == 0) {
            Log::Trace("set_digital: LOW");
            pinMode(pin, OUTPUT);
            digitalWrite(pin, LOW);
            return 0;
        }

        Log::Error("set_digital: unknown level");
        return 2;
    }
};
