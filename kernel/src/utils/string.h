#ifndef MOSS_KERN_STRING_H
#define MOSS_KERN_STRING_H

void s8print(s8 str);

Lsize strlen(char* s);
void strrev(char* str);

u32 digits(u32 n, i32 base);
void itoa(i32 num, i32 base, char buffer[]);

#endif // MOSS_KERN_STRING_H
