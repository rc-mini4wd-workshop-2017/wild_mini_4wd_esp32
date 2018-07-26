#pragma once

#include "Command.h"
#include "Servo.h"

class GetDistanceCommand : public Command {
public:
    GetDistanceCommand() {
        pinMode(kTrigger, OUTPUT);
        pinMode(kEcho,    INPUT);
    }
    ~GetDistanceCommand() {}

public:
    const char *GetName() {
        return "get_distance";
    }

    int Execute(const CommandLineParser *parser) {
        int distance = GetDistance();
        reply("distance=");
        reply(distance);
        reply("\n");
        return 0;
    }

    float GetDistance() {
        float distance = 0;
        for (int i=0; i<kRetryTimes; i++) {
            distance += (getDistanceOne() / kRetryTimes);
        }
        return distance;
    }

private:
    float getDistanceOne() {
        digitalWrite(kTrigger, HIGH);
        vTaskDelay(20);
        digitalWrite(kTrigger, LOW);

        int intervalUs = pulseIn(kEcho, HIGH) / 2;
        float distance = intervalUs * 340.0 / 1000.0 / 1000.0 * 100;
        if (distance > kDistanceMax) {
            Log::Error("get_distance: max distance");
            return kDistanceMax;
        }
        return distance;
    }

    enum {
        kTrigger     = 32,
        kEcho        = 33,
        kRetryTimes  = 3,
        kDistanceMax = 300,
    };
};
