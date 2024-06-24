/* 
 * IMPORTANT
 * =========
 * This file is automatically included in to every single compiled program.
 * The types defined in this file are the standard and preferable types for 
 * programs written for moss.
 */

#ifndef MOSS_DEFINES_H
#define MOSS_DEFINES_H

#define countof(a)    (Size)(sizeof(a) / sizeof(*(a)))
#define lengthof(s)   (countof(s) - 1)

#define asm __asm__
#define null nullptr // null doesnt have to yell at you


typedef  __UINT8_TYPE__         u8;
typedef  __UINT16_TYPE__        u16;
typedef  __UINT32_TYPE__        u32;
typedef  __UINT64_TYPE__        u64;

typedef  __UINT_LEAST8_TYPE__   uLeast8;
typedef  __UINT_LEAST16_TYPE__  uLeast16;
typedef  __UINT_LEAST32_TYPE__  uLeast32;
typedef  __UINT_LEAST64_TYPE__  uLeast64;

typedef  __UINT_FAST8_TYPE__    uFast8;
typedef  __UINT_FAST16_TYPE__   uFast16;
typedef  __UINT_FAST32_TYPE__   uFast32;
typedef  __UINT_FAST64_TYPE__   uFast64;

typedef  __INT8_TYPE__          i8;
typedef  __INT16_TYPE__         i16;
typedef  __INT32_TYPE__         i32;
typedef  __INT64_TYPE__         i64;

typedef  __INT_LEAST8_TYPE__    iLeast8;
typedef  __INT_LEAST16_TYPE__   iLeast16;
typedef  __INT_LEAST32_TYPE__   iLeast32;
typedef  __INT_LEAST64_TYPE__   iLeast64;

typedef  __INT_FAST8_TYPE__     iFast8;
typedef  __INT_FAST16_TYPE__    iFast16;
typedef  __INT_FAST32_TYPE__    iFast32;
typedef  __INT_FAST64_TYPE__    iFast64;

typedef  __UINTPTR_TYPE__       uintptr;
typedef  __INTPTR_TYPE__        intptr;
typedef  __PTRDIFF_TYPE__       ptrdiff;

typedef  __UINTMAX_TYPE__       uintmax;
typedef  __INTMAX_TYPE__        intmax;

typedef i32 Size;
typedef u32 Usize;
typedef i64 Lsize; // L stands for large since long typically means 32 bit
typedef u64 Lusize;
typedef u8  Byte;

#define s8(s) (s8){ (Byte*)s, lengthof(s) }
#define s8f(s,n) (s8){ (Byte[n])s, lengthof(s) }
typedef struct {
    Byte* ptr;
    Size length;
} s8;


#endif // MOSS_DEFINES_H
