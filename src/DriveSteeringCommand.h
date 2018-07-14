#pragma once

#include "Command.h"
#include "SetServoCommand.h"

class DriveSteeringCommand : public Command {
public:
    DriveSteeringCommand() {}
    ~DriveSteeringCommand() {}

public:
    virtual void Initialize(SetServoCommand *servo) {
        this->servo = servo;
    }

    const char *GetName() {
        return "drive_steering";
    }

    int Execute(const CommandLineParser *parser) {
        const char *direction = parser->GetFirstArg();
        if (direction == 0) {
            Log::Trace("drive_steering: (default: FORWARD)");
            return servo->Drive(kForward);
        }

        if (strcmp(direction, "LEFT") == 0) {
            Log::Trace("drive_steering: LEFT");
            return servo->Drive(kLeft);
        } else if (strcmp(direction, "RIGHT") == 0) {
            Log::Trace("drive_steering: RIGHT");
            return servo->Drive(kRight);
        } else if (strcmp(direction, "FORWARD") == 0) {
            Log::Trace("drive_steering: FORWARD");
            return servo->Drive(kForward);
        }

        Log::Error("drive_motor: unknown direction");
        return 3;
    }

private:
    enum {
        kLeft    = 62,
        kRight   = 92,
        kForward = 77,
    };

    SetServoCommand *servo;
};
