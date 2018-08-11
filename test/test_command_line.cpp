// Copyright 2018 Quattro Ace. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#include "unit_test.hpp"

#include "stdint.h"
#include "string.h"
#include "Log.h"
#include "Log.cpp"

#include "Stream.h"
#include "MemoryStream.h"
#include "FakeSerial.h"

#include "CommandLine.h"
#include "CommandLine.cpp"

class TestCommand : public Command {
public:
    TestCommand() {}
    ~TestCommand() {}

public:
    const char *GetName() {
        return "test";
    }
    int Execute(const CommandLineParser *parser) {
        return 0;
    }
};

void test_initialize()
{
    MemoryStream stream;
    CommandLine cl;
    cl.Initialize(&stream);
}

void test_add_command()
{
    MemoryStream stream;
    CommandLine cl;
    cl.Initialize(&stream);

    TestCommand command;
    cl.AddCommand(&command);
}

void test_analyze()
{
    MemoryStream stream;
    CommandLine cl;
    cl.Initialize(&stream);

    TestCommand command;
    cl.AddCommand(&command);

    stream.AppendReadBuffer("test 0 1 2 \n");
    cl.Analyze();
}

int main(int argc, char **argv)
{
    UT_RUN(test_initialize);
    UT_RUN(test_add_command);
    UT_RUN(test_analyze);
    return 0;
}

