#ifndef MOSS_MEMORY_H
#define MOSS_MEMORY_H

typedef __SIZE_TYPE__ size_t; // IMPORTANT: this should not be used anywhere else

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

#endif // MOSS_MEMORY_H

