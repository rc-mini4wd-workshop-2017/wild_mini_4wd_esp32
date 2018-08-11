// Copyright 2018 Quattro Ace. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#pragma once

#include "command/Command.h"
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
        const char *value = parser->NextArg(until);
        bool isTimeout = false;
        if (strcmp(until, "UNTIL_TIME") == 0) {
            if (value == 0) {
                Log::Error("drive_motor: not found UNTIL_TIME's value");
                return result;
            }
            int timeout = atoi(value);
            Log::Trace("drive_motor: UNTIL_TIME");
            vTaskDelay(timeout * 1000);
        } else if (strcmp(until, "UNTIL_NEAR") == 0) {
            if (value == 0) {
                Log::Error("drive_motor: not found UNTIL_NEAR's value");
                return result;
            }
            int nearDistance = atoi(value);
            Log::Trace("drive_motor: UNTIL_NEAR");
            driveUntilNear(nearDistance, &isTimeout);
        } else if (strcmp(until, "UNTIL_BUMPER") == 0) {
            driveUntilBumper(&isTimeout);
        } else {
            Log::Error("drive_motor: until_xxx");
            return result;
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
        kStopControl      = 0,
    };

    SetMotorCommand       *motor;
    GetDistanceCommand    *distance;
    GetButtonStateCommand *button;

    void driveUntilNear(int nearDistance, bool *isTimeout) {
        Log::Trace("drive_motor: until near");
        for (int i=0; i<kDistanceTimesMax; i++) {
            if (distance->GetDistance() < nearDistance) {
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
