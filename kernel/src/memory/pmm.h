#ifndef MOSS_KERN_PMM_H
#define MOSS_KERN_PMM_H

typedef struct {
   u64 addr;
   u64 length;
   bool used;
} MemRegion;


#endif // MOSS_KERN_PMM_H
