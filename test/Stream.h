// Copyright 2018 Quattro Ace. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#pragma once

class Stream {
public:
    Stream() {}
    virtual ~Stream() {}

public:
    virtual int available() = 0;
    virtual int read() = 0;
    virtual size_t write(uint8_t ch) = 0;
    virtual size_t write(const char *str) = 0;
    virtual size_t write(const uint8_t *buffer, size_t size) = 0;
    virtual size_t print(int i) = 0;
};
