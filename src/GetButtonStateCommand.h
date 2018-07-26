#pragma once

#include "Command.h"

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
