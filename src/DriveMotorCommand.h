#pragma once

#include "Command.h"
#include "SetMotorCommand.h"

class DriveMotorCommand : public Command {
public:
    DriveMotorCommand() {}
    ~DriveMotorCommand() {}

public:
    virtual void Initialize(SetMotorCommand *motor) {
        this->motor = motor;
    }

    const char *GetName() {
        return "drive_motor";
    }

    int Execute(const CommandLineParser *parser) {
        const char *direction = parser->GetFirstArg();
        if (direction == 0) {
            Log::Info("drive_motor: STOP");
            return motor->Drive(kStopControl);
        }

        if (strcmp(direction, "STOP") == 0) {
            Log::Info("drive_motor: STOP");
            return motor->Drive(kStopControl);
        }
        if (strcmp(direction, "FORWARD") == 0) {
            Log::Info("drive_motor: FORWARD");
            return motor->Drive(kForwardControl);
        }
        if (strcmp(direction, "BACKWARD") == 0) {
            Log::Info("drive_motor: BACKWARD");
            return motor->Drive(kBackwardControl);
        }

        Log::Error("drive_motor: unknown direction");
        return 3;
    }

private:
    enum {
        kStopControl     = 0,
        kForwardControl  = 81,
        kBackwardControl = 82,
    };

    SetMotorCommand *motor;
};
