// Copyright 2018 Quattro Ace. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#include "BluetoothSerial.h"
#include "Log.h"
#include "CommandLine.h"
#include "InfoCommand.h"
#include "LogCommand.h"
#include "GetButtonStateCommand.h"
#include "SetLogLevelCommand.h"
#include "SetDigitalCommand.h"
#include "SetServoCommand.h"
#include "DriveSteeringCommand.h"
#include "SetMotorCommand.h"
#include "DriveMotorCommand.h"
#include "GetDistanceCommand.h"

enum {
    kDebugLed = 26,
};

BluetoothSerial stream;

CommandLine           commandLine;
InfoCommand           infoCommand;
LogCommand            logCommand;
GetButtonStateCommand getButtonStateCommand;
SetLogLevelCommand    setLogLevelCommand;
SetDigitalCommand     setDigitalCommand;
SetServoCommand       setServoCommand;
DriveSteeringCommand  driveSteeringCommand;
SetMotorCommand       setMotorCommand;
DriveMotorCommand     driveMotorCommand;
GetDistanceCommand    getDistanceCommand;

void setup()
{
    pinMode(kDebugLed, OUTPUT);
    digitalWrite(kDebugLed, HIGH);
    Serial.begin(115200);
    stream.begin("Quattro Ace");

    commandLine.Initialize(&stream);

    infoCommand.Initialize(&stream);
    commandLine.AddCommand(&infoCommand);

    logCommand.Initialize(&stream);
    commandLine.AddCommand(&logCommand);

    getButtonStateCommand.Initialize(&stream);
    commandLine.AddCommand(&getButtonStateCommand);

    commandLine.AddCommand(&setLogLevelCommand);
    commandLine.AddCommand(&setDigitalCommand);
    commandLine.AddCommand(&setServoCommand);

    driveSteeringCommand.Initialize(&setServoCommand);
    commandLine.AddCommand(&driveSteeringCommand);

    setMotorCommand.Initialize(&stream);
    commandLine.AddCommand(&setMotorCommand);

    driveMotorCommand.Initialize(&stream,
                                 &setMotorCommand,
                                 &getDistanceCommand,
                                 &getButtonStateCommand);
    commandLine.AddCommand(&driveMotorCommand);

    commandLine.AddCommand(&getDistanceCommand);

    Log::Info("Quattro Ace started...");
    digitalWrite(kDebugLed, LOW);
}

void loop()
{
    digitalWrite(kDebugLed, LOW);
    commandLine.Analyze();

    static int executeTimes = 0;
    if (executeTimes > 100) {
        executeTimes = 0;
    } else if (executeTimes > 50) {
        digitalWrite(kDebugLed, HIGH);
    } else {
        digitalWrite(kDebugLed, LOW);
    }
    ++executeTimes;

    // Task watchdog got triggered.
    // https://github.com/espressif/arduino-esp32/issues/595
    vTaskDelay(10);
}
