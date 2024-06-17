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

#define null    ((void*)0)
#define nullptr ((void*)0)

typedef unsigned int  Size;

typedef char        Byte;

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

typedef  __UINTMAX_TYPE__       uintmax;
typedef  __INTMAX_TYPE__        intmax;

typedef enum {
    false = 0,
    true = 1
} Bool;

#define s8(s) (s8){ (Byte*)s, lengthof(s) }
typedef struct {
    Byte* str;
    Size length;
} s8;

// returns -1 if no match 0 if they match
// int s8cmp(s8 a, s8 b) {
//    // obviously not the same if they aren't the same length
//    if (a.length != b.length) return -1;
//    for (Size i = 0; i < a.length; i++) {
//       if (a.str[i] != b.str[i]) return -1;
//    }
//    return 0;
// }

#endif // MOSS_DEFINES_H
