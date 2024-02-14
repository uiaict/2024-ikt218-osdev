#pragma once

// va_list
typedef __builtin_va_list va_list;

// va_start
#define va_start(v, l) __builtin_va_start(v, l)

// va_end
#define va_end(v) __builtin_va_end(v)

// va_arg
#define va_arg(v, l) __builtin_va_arg(v, l)

