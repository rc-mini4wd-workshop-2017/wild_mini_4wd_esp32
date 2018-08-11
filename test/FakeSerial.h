// Copyright 2018 Quattro Ace. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#pragma once

#include <iostream>
#include "IOStream.h"

class FakeSerial : public IOStream {
public:
    FakeSerial() : IOStream(std::cin, std::cout) {}
    virtual ~FakeSerial() {}
};

FakeSerial Serial;
