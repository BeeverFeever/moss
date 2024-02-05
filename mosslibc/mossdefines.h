#ifndef MOSS_DEFINES_H
#define MOSS_DEFINES_H

#include <mossint.h>

#define NULL    ((void*)0)
#define nullptr ((void*)0)

typedef __SIZE_TYPE__ size_t; // this is purely here for the required memory
                             // functions in mossmemory.h
                             // IMPORTANT: this should not be used anywhere else
typedef signed int  Size;

typedef char        Byte;
typedef char*       String;

typedef uint8_t     U8;
typedef uint16_t    U16;
typedef uint32_t    U32;
typedef uint64_t    U64;

typedef int8_t      I8;
typedef int16_t     I16;
typedef int32_t     I32;
typedef int64_t     I64;

typedef enum {
    false = 0,
    true = 1
} bool;

#endif // MOSS_DEFINES_H
