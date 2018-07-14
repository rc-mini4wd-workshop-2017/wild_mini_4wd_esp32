#pragma once

#include "Command.h"
#include "Wire.h"

class SetMotorCommand : public Command {
public:
    SetMotorCommand() {}
    ~SetMotorCommand() {}

public:
    virtual void Initialize(Stream *stream) {
        Command::Initialize(stream);
        pinMode(kI2cSda, INPUT_PULLUP);
        pinMode(kI2cScl, INPUT_PULLUP);
        Wire.begin();
        Wire.setClock(10000);
    }

    const char *GetName() {
        return "set_motor";
    }

    int Execute(const CommandLineParser *parser) {
        const char *arg = parser->GetFirstArg();
        int control = 0;
        if (arg != 0) {
            control = atoi(arg);
        }

        for (int i=0; i<10; i++) {
            Wire.beginTransmission(kRv8830Address);
            Wire.write(kRv8830Control);
            Wire.write(control);

            int result = Wire.endTransmission();
            switch (result) {
            case 0: Log::Info("set_motor: success");                          return 0;
            case 1: Log::Error("set_motor: buffer overflow error");           return -1;
            case 2: Log::Error("set_motor: slave addr: nack received error"); return -2;
            case 3: Log::Error("set_motor: data: nack received error");       return -3;
            case 4: Log::Error("set_motor: error");                           return -4;
            }
            // workaround for esp-32 i2c bug
            // see http://d.hatena.ne.jp/wakwak_koba/20171228
            // see https://github.com/espressif/arduino-esp32/issues/349
            Wire.reset();
            Log::Error("set_motor: unknown result error");
        }

        return 3;
    }

private:
    enum {
        kRv8830Control = 0,
        kRv8830Address = 100,
        kI2cSda        = 21,
        kI2cScl        = 22,
    };
};
