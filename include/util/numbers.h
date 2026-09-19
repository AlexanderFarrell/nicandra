#ifndef NICANDRA_NUMBERS_H
#define NICANDRA_NUMBERS_H

#include <stdint.h>

#define true 1
#define false 0

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t
#define i8 int8_t
#define i16 int16_t
#define i32 int32_t
#define i64 int64_t

typedef enum Bool Bool;
enum Bool {
    TRUE = 1,
    FALSE = 0,
};

#endif