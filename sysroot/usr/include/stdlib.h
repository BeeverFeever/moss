#ifndef _STDLIB_H
#define _STDLIB_H
#ifdef __cplusplus
extern "C" {
#endif
void exit(int);
void abort(void);
int atexit(void (*)(void));
int atoi(const char*);
int abs(int);
void free(void*);
char* getenv(const char*);
void* malloc(size_t);
void* calloc(size_t, size_t);
#ifdef __cplusplus
}
#endif
#endif
