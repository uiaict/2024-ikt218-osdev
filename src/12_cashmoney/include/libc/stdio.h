#pragma once

#include <libc/stdint.h>

int putchar(int c);
bool print(const char* data, size_t length);
int printf(const char* __restrict__ format, ...);

void monitor_put(char c);
void monitor_clear();
void monitor_write(const char *c_str);
void monitor_write_hex(uint32_t number);
void monitor_write_udec(uint32_t number);
void monitor_write_sdec(int32_t number);
void monitor_write_bool(bool b);