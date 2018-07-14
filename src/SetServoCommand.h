#pragma once

#include "Command.h"
#include "Servo.h"

class SetServoCommand : public Command {
public:
    SetServoCommand() {}
    ~SetServoCommand() {}

public:
    const char *GetName() {
        return "set_servo";
    }

    int Execute(const CommandLineParser *parser) {
        const char *arg = parser->GetFirstArg();
        if (arg == 0) {
            Log::Error("set_servo: no angle");
            return 2;
        }

        Drive(atoi(arg));
        return 0;
    }

    int Drive(int degrees) {
        Servo servo;
        servo.attach(kPin);
        servo.write(degrees);
        vTaskDelay(200);
        servo.detach();
        return 0;
    }

private:
    enum {
        kPin = 12,
    };
};
