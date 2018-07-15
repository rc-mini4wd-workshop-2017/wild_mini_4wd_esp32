#pragma once

#include "Command.h"
#include "SetMotorCommand.h"
#include "GetDistanceCommand.h"

class DriveMotorCommand : public Command {
public:
    DriveMotorCommand() {}
    ~DriveMotorCommand() {}

public:
    virtual void Initialize(SetMotorCommand *motor, GetDistanceCommand *distance) {
        this->motor    = motor;
        this->distance = distance;
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
            Log::Trace("drive_motor: FORWARD");
            int result = motor->Drive(kForwardControl);
            if (result != 0) {
                Log::Error("drive_motor: FORWARD");
                return result;
            }
        } else if (strcmp(direction, "BACKWARD") == 0) {
            Log::Trace("drive_motor: BACKWARD");
            int result = motor->Drive(kBackwardControl);
            if (result != 0) {
                Log::Error("drive_motor: BACKWARD");
                return result;
            }
        }

        const char *until = parser->NextArg(direction);
        if (until == 0) {
            Log::Trace("drive_motor: interval");
            vTaskDelay(kInterval);
        } else if (strcmp(until, "UNTIL_NEAR") == 0) {
            Log::Trace("drive_motor: until near");
            for (int i=0; i<kDistanceTimesMax; i++) {
                if (distance->GetDistance() < kNearDistance) {
                    Log::Error("drive_motor: UNTIL_NEAR timeout");
                    break;
                }
            }
        }

        int result = motor->Drive(kStopControl);
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
        kInterval         = 2000,
        kStopControl      = 0,
        kForwardControl   = 81,
        kBackwardControl  = 82,
    };

    SetMotorCommand    *motor;
    GetDistanceCommand *distance;
};
