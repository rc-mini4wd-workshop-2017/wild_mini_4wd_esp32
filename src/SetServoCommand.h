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
            Log::Error("set_servo: invalid index");
            return 1;
        }
        int pin = atoi(arg);

        arg = parser->NextArg(arg);
        if (arg == 0) {
            Log::Error("set_servo: invalid angle");
            return 2;
        }
        int degrees = atoi(arg);

        Servo servo;
        servo.attach(pin);
        servo.write(degrees);
        vTaskDelay(200);
        servo.detach();

        return 0;
    }
};
