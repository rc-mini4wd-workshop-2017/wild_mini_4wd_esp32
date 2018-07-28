// Copyright 2018 Quattro Ace. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#pragma once

#include "Command.h"
#include "SetMotorCommand.h"
#include "GetDistanceCommand.h"

class DriveMotorCommand : public Command {
public:
    DriveMotorCommand() {}
    ~DriveMotorCommand() {}

public:
    virtual void Initialize(Stream *stream,
                            SetMotorCommand *motor,
                            GetDistanceCommand *distance,
                            GetButtonStateCommand *button) {
        Command::Initialize(stream);
        this->motor    = motor;
        this->distance = distance;
        this->button   = button;
    }

    const char *GetName() {
        return "drive_motor";
    }

    int Execute(const CommandLineParser *parser) {
        const char *arg = parser->GetFirstArg();
        if (arg == 0) {
            Log::Error("drive_motor: no vset");
            return 2;
        }

        int control = atoi(arg);
        int result = motor->Drive(control);
        if (result != 0) {
            Log::Error("drive_motor: START");
            return result;
        }

        const char *until = parser->NextArg(arg);
        bool isTimeout = false;
        if (until == 0) {
            Log::Trace("drive_motor: interval");
            vTaskDelay(kInterval);
        } else if (strcmp(until, "UNTIL_NEAR") == 0) {
            driveUntilNear(&isTimeout);
        } else if (strcmp(until, "UNTIL_BUMPER") == 0) {
            driveUntilBumper(&isTimeout);
        }

        if (isTimeout) {
            Log::Info("drive_motor: timeout");
            reply("drive_motor: timeout\n");
        }
        result = motor->Drive(kStopControl);
        if (result != 0) {
            Log::Error("drive_motor: STOP");
            return result;
        }

        return 0;
    }

private:
    enum {
        kNearDistance     = 15,
        /**
         * GetDistance() : 60ms
         * GetDistance() x kDistanceTimesMax : 12s
         */
        kDistanceTimesMax = 200,
        /**
         * kBumperInterval : 60ms
         * kBumperInterval x kBumperTimesMax : 12s
         */
        kBumperInterval   = 60,
        kBumperTimesMax   = 200,
        kInterval         = 2000,
        kStopControl      = 0,
    };

    SetMotorCommand       *motor;
    GetDistanceCommand    *distance;
    GetButtonStateCommand *button;

    void driveUntilNear(bool *isTimeout) {
        Log::Trace("drive_motor: until near");
        for (int i=0; i<kDistanceTimesMax; i++) {
            if (distance->GetDistance() < kNearDistance) {
                Log::Info("drive_motor: detected UNTIL_NEAR");
                *isTimeout = false;
                return;
            }
        }
        *isTimeout = true;
    }

    void driveUntilBumper(bool *isTimeout) {
        Log::Trace("drive_motor: until bumper");
        for (int i=0; i<kBumperTimesMax; i++) {
            if (button->IsPressed()) {
                Log::Info("drive_motor: detected UNTIL_BUMPER");
                *isTimeout = false;
                return;
            }
            vTaskDelay(kBumperInterval);
        }
        *isTimeout = true;
    }
};
