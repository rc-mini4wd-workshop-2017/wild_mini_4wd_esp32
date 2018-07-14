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
            Log::Error("drive_motor: no direction");
            return 2;
        }

        if (strcmp(direction, "FORWARD") == 0) {
            Log::Info("drive_motor: FORWARD");
            int result = motor->Drive(kForwardControl);
            if (result != 0) {
                return result;
            }
            vTaskDelay(kInterval);
            return motor->Drive(kStopControl);
        } else if (strcmp(direction, "BACKWARD") == 0) {
            Log::Info("drive_motor: BACKWARD");
            int result = motor->Drive(kBackwardControl);
            if (result != 0) {
                return result;
            }
            vTaskDelay(kInterval);
            return motor->Drive(kStopControl);
        }

        Log::Error("drive_motor: unknown direction");
        return 3;
    }

private:
    enum {
        kInterval        = 2000,
        kStopControl     = 0,
        kForwardControl  = 81,
        kBackwardControl = 82,
    };

    SetMotorCommand *motor;
};
