#include "common.h"

void monitor_put(char c);
void monitor_clear();
void monitor_write(const char *c_str);
void monitor_write_hex(uint32_t number);
void monitor_write_udec(uint32_t number);
void monitor_write_sdec(int32_t number);