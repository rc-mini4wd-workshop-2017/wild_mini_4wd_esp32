#include "BluetoothSerial.h"
#include "Log.h"
#include "CommandLine.h"

BluetoothSerial stream;
CommandLine cmd;

void setup()
{
    Serial.begin(115200);
    stream.begin("Quattro Ace");
    cmd.Initialize(&stream);
    Log::Info("Quattro Ace started...");
}

void loop()
{
    cmd.Analyze();

    // Task watchdog got triggered.
    // https://github.com/espressif/arduino-esp32/issues/595
    vTaskDelay(10);
}
