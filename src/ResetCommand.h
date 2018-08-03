// Copyright 2018 Quattro Ace. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#pragma once

#include "Command.h"
#include "SetMotorCommand.h"
#include "SetServoCommand.h"

class ResetCommand : public Command {
public:
    ResetCommand() {}
    ~ResetCommand() {}

public:
    virtual void Initialize(Stream *stream,
                            SetMotorCommand *motor,
                            SetServoCommand *servo) {
        Command::Initialize(stream);
        this->motor = motor;
        this->servo = servo;
    }

    const char *GetName() {
        return "reset";
    }

    int Execute(const CommandLineParser *parser) {
        motor->Drive(0);
        servo->Drive(90);
        return 0;
    }

private:
    SetMotorCommand *motor;
    SetServoCommand *servo;
};
