#pragma once

typedef struct {
    u16 limit;
    u64 base;
} __attribute__((packed)) GDTR;

// NOTE: array size needs to be chanegd accordingly if more entries are added to
// gdt
typedef struct {
    u64 entries[10];
} GDT;

void gdt_init(void);
