#ifndef MOSS_DEFINES_H
#define MOSS_DEFINES_H

#include <mossint.h>

#define countof(a)    (size)(sizeof(a) / sizeof(*(a)))
#define lengthof(s)   (countof(s) - 1)

#define NULL    ((void*)0)
#define nullptr ((void*)0)

typedef __SIZE_TYPE__ size_t; // this is purely here for the required memory
                             // functions in mossmemory.h
                             // IMPORTANT: this should not be used anywhere else
typedef signed int  Size;

typedef char        Byte;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

typedef enum {
    false = 0,
    true = 1
} Bool;

#endif // MOSS_DEFINES_H
