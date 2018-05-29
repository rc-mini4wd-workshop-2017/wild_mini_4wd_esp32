#include "BluetoothSerial.h"
#include "Log.h"
#include "CommandLine.h"
#include "InfoCommand.h"
#include "LogCommand.h"
#include "SetLogLevelCommand.h"
#include "SetDigitalCommand.h"
#include "SetServoCommand.h"
#include "SetMotorCommand.h"

BluetoothSerial stream;

CommandLine        commandLine;
InfoCommand        infoCommand;
LogCommand         logCommand;
SetLogLevelCommand setLogLevelCommand;
SetDigitalCommand  setDigitalCommand;
SetServoCommand    setServoCommand;
SetMotorCommand    setMotorCommand;

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

    setMotorCommand.Initialize(&stream);
    commandLine.AddCommand(&setMotorCommand);

    Log::Info("Quattro Ace started...");
}

void loop()
{
    commandLine.Analyze();

    // Task watchdog got triggered.
    // https://github.com/espressif/arduino-esp32/issues/595
    vTaskDelay(10);
}
