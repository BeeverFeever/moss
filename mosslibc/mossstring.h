#ifndef MOSS_STRING_H
#define MOSS_STRING_H

#define s8(s) (s8){ (Byte*)s, lengthof(s) }

typedef struct {
    Byte* str;
    Size length;
} s8;

#endif // MOSS_STRING_H
