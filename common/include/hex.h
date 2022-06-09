/* SPDX-License-Identifier: LGPL-3.0-or-later */
/* Copyright (C) 2022 OSCAR lab, Stony Brook University
 *                    University of North Carolina at Chapel Hill
 *                    Intel Corporation
 */

#ifndef HEX_H
#define HEX_H

#include <stddef.h>
#include <stdint.h>

#include "api.h"

static inline char* bytes2hex(const void* bytes, size_t bytes_size, char* hex, size_t hex_size) {
    if (hex_size < bytes_size * 2 + 1)
        return NULL;

    static const char* ch = "0123456789abcdef";
    for (size_t i = 0; i < bytes_size; i++) {
        unsigned char b = ((unsigned char*)bytes)[i];
        hex[i * 2]     = ch[b / 16];
        hex[i * 2 + 1] = ch[b % 16];
    }

    hex[bytes_size * 2] = 0;
    return hex;
}

static inline int8_t hex2dec(char hex) {
    if (hex >= 'A' && hex <= 'F')
        return hex - 'A' + 10;
    else if (hex >= 'a' && hex <= 'f')
        return hex - 'a' + 10;
    else if (hex >= '0' && hex <= '9')
        return hex - '0';
    else
        return -1;
}

static inline void* hex2bytes(const char* hex, size_t hex_size, void* bytes, size_t bytes_size) {
    if (hex_size < bytes_size * 2 + 1)
        return NULL;

    for (size_t i = 0; i < hex_size - 1; i += 2) {
        int8_t hi = hex2dec(hex[i]);
        int8_t lo = hex2dec(hex[i+1]);
        if (hi < 0 || lo < 0)
            return NULL;
        ((unsigned char*)bytes)[i / 2] = hi * 16 + lo;
    }

    return bytes;
}

#endif // HEX_H
