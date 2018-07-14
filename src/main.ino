#include "BluetoothSerial.h"
#include "Log.h"
#include "CommandLine.h"
#include "InfoCommand.h"
#include "LogCommand.h"
#include "SetLogLevelCommand.h"
#include "SetDigitalCommand.h"
#include "SetServoCommand.h"
#include "DriveSteeringCommand.h"
#include "SetMotorCommand.h"
#include "DriveMotorCommand.h"
#include "GetDistanceCommand.h"

BluetoothSerial stream;

CommandLine          commandLine;
InfoCommand          infoCommand;
LogCommand           logCommand;
SetLogLevelCommand   setLogLevelCommand;
SetDigitalCommand    setDigitalCommand;
SetServoCommand      setServoCommand;
DriveSteeringCommand driveSteeringCommand;
SetMotorCommand      setMotorCommand;
DriveMotorCommand    driveMotorCommand;
GetDistanceCommand   getDistanceCommand;

void setup()
{
    Serial.begin(115200);
    stream.begin("Quattro Ace");

    commandLine.Initialize(&stream);

    infoCommand.Initialize(&stream);
    commandLine.AddCommand(&infoCommand);

    logCommand.Initialize(&stream);
    commandLine.AddCommand(&logCommand);

    commandLine.AddCommand(&setLogLevelCommand);
    commandLine.AddCommand(&setDigitalCommand);
    commandLine.AddCommand(&setServoCommand);

    driveSteeringCommand.Initialize(&setServoCommand);
    commandLine.AddCommand(&driveSteeringCommand);

    setMotorCommand.Initialize(&stream);
    commandLine.AddCommand(&setMotorCommand);

    driveMotorCommand.Initialize(&setMotorCommand);
    commandLine.AddCommand(&driveMotorCommand);

    commandLine.AddCommand(&getDistanceCommand);

    Log::Info("Quattro Ace started...");
}

void loop()
{
    commandLine.Analyze();

    // Task watchdog got triggered.
    // https://github.com/espressif/arduino-esp32/issues/595
    vTaskDelay(10);
}
