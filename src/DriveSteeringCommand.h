// Copyright 2018 Quattro Ace. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

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
        kLeft    = 75,
        kRight   = 105,
        kForward = 90,
    };

    SetServoCommand *servo;
};
