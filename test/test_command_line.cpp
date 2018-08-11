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
    TestCommand() : countOfExecute(0) {}
    ~TestCommand() {}

public:
    virtual const char *GetName() {
        return "test";
    }
    virtual int Execute(const CommandLineParser *parser) {
        ++countOfExecute;

        const char *arg = parser->GetFirstArg();
        UT_ASSERT_STRING("0", arg);
        UT_ASSERT_STRING("1", arg = parser->NextArg(arg));
        UT_ASSERT_STRING("2", arg = parser->NextArg(arg));
        return 0;
    }
    int GetCountOfExecute() {
        return countOfExecute;
    }

private:
    int countOfExecute;
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

    stream.AppendReadBuffer("test 0 1 2\n");
    cl.Analyze();
    UT_ASSERT_INT(1, command.GetCountOfExecute());
}

int main(int argc, char **argv)
{
    UT_RUN(test_initialize);
    UT_RUN(test_add_command);
    UT_RUN(test_analyze);
    return 0;
}

