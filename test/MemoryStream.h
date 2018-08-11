// Copyright 2018 Quattro Ace. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#pragma once

#include <sstream>
#include "IOStream.h"

class MemoryStream : public IOStream {
public:
    MemoryStream() : IOStream(readStream, writeStream) {}
    virtual ~MemoryStream() {}

public:
    void AppendReadBuffer(const char *buffer) {
        int length = strlen(buffer);
        AppendReadBuffer((const uint8_t*)buffer, length);
    }
    void AppendReadBuffer(const uint8_t *buffer, size_t size) {
        for (size_t i=0; i<size; i++) {
            readStream << buffer[i];
        }
    }

private:
    std::stringstream readStream;
    std::stringstream writeStream;
};
