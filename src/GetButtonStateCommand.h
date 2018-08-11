// Copyright 2018 Quattro Ace. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#pragma once

#include "command/Command.h"

class GetButtonStateCommand : public Command {
public:
    GetButtonStateCommand() {
        pinMode(kButton, INPUT);
    }
    ~GetButtonStateCommand() {}

public:
    const char *GetName() {
        return "get_button_state";
    }

    int Execute(const CommandLineParser *parser) {
        if (IsPressed()) {
            reply("button state: pressed\n");
        } else {
            reply("button state: not pressed\n");
        }
        return 0;
    }

    bool IsPressed() {
        return digitalRead(kButton) == LOW;
    }

private:
    enum {
        kButton = 34,
    };
};
