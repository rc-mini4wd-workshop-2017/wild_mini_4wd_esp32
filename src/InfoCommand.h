// Copyright 2018 Quattro Ace. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#pragma once

#include "Command.h"
#include "Version.h"

class InfoCommand : public Command {
public:
    InfoCommand() {}
    ~InfoCommand() {}

public:
    const char *GetName() {
        return "info";
    }

    int Execute(const CommandLineParser *parser) {
        reply("version=");
        reply(VERSION);
        reply("\n");
        return 0;
    }
};
