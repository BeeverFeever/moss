#pragma once

typedef struct {
    U16 limit;
    U64 base;
} __attribute__((packed)) GDTR;

// NOTE: array size needs to be chanegd accordingly if more entries are added to
// gdt
typedef struct {
    U64 entries[10];
} GDT;

void gdt_init(void);
