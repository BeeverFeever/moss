#ifndef MOSS_KERN_UTILS_H
#define MOSS_KERN_UTILS_H

void *memcpy(void *dest, const void *src, Size n);
void *memset(void *s, int c, Size n);
void *memmove(void *dest, const void *src, Size n);
int memcmp(const void *s1, const void *s2, Size n);

#endif // MOSS_KERN_UTILS_H
