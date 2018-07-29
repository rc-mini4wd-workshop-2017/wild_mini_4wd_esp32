// Copyright 2018 Quattro Ace. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#include "Arduino.h"
#include "Version.h"
#include "Log.h"
#include "Wire.h"
#include "Servo.h"

enum {
    kRv8830Control  = 0,
    kRv8830Address  = 100,
    kI2cSda         = 21,
    kI2cScl         = 22,
    kServo          = 12,
    kDebugLed       = 26,
};

int DriveMotor(int control) {
    Wire.beginTransmission(kRv8830Address);
    Wire.write(kRv8830Control);
    Wire.write(control);

    int result = Wire.endTransmission();
    switch (result) {
    case 0: Log::Trace("set_motor: success");                         return 0;
    case 1: Log::Error("set_motor: buffer overflow error");           return -1;
    case 2: Log::Error("set_motor: slave addr: nack received error"); return -2;
    case 3: Log::Error("set_motor: data: nack received error");       return -3;
    case 4: Log::Error("set_motor: error");                           return -4;
    }
    // workaround for esp-32 i2c bug
    // see http://d.hatena.ne.jp/wakwak_koba/20171228
    // see https://github.com/espressif/arduino-esp32/issues/349
    // Wire.reset();
    Log::Error("set_motor: unknown result error(workaround for esp-32 i2c bug)");
    return 3;
}

int DriveServo(int degrees) {
    Servo servo;
    servo.attach(kServo);
    servo.write(degrees);
    vTaskDelay(200);
    servo.detach();
    return 0;
}

void setup()
{
    pinMode(kDebugLed, OUTPUT);
    digitalWrite(kDebugLed, HIGH);

    pinMode(kI2cSda, INPUT_PULLUP);
    pinMode(kI2cScl, INPUT_PULLUP);
    Wire.begin();
    Wire.setClock(10000);

    Serial.begin(115200);

    Log::Info("Quattro Ace started...");
    Log::Info(VERSION);
    digitalWrite(kDebugLed, LOW);
}

void loop()
{
    // go forward
    DriveMotor(0x61);
    vTaskDelay(3000);

    // stop
    DriveMotor(0);
    vTaskDelay(1000);

    // go backward
    DriveMotor(0x61);
    vTaskDelay(3000);

    // stop
    DriveMotor(0);
    vTaskDelay(1000);

    // Task watchdog got triggered.
    // https://github.com/espressif/arduino-esp32/issues/595
    vTaskDelay(10);
}
