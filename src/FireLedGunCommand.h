// Copyright 2018 Quattro Ace. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#pragma once

#include "command/Command.h"

class FireLedGunCommand : public Command {
public:
    FireLedGunCommand() {}
    ~FireLedGunCommand() {}

public:
    const char *GetName() {
        return "fire_led_gun";
    }

    int Execute(const CommandLineParser *parser) {
        const char *arg = parser->GetFirstArg();
        if (arg == 0) {
            Log::Error("fire_led_gun: invalid index");
            return 1;
        }
        int pin = atoi(arg);

        Log::Trace("fire_led_gun: fire");
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH);
        vTaskDelay(100);
        digitalWrite(pin, LOW);
        return 0;
    }
};
