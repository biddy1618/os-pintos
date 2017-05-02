#ifndef VM_FRAME_H
#define VM_FRAME_H

#include "vm/page.h"
#include "threads/palloc.h"


void frame_init (void);
void *frame_alloc (enum palloc_flags flags, struct spte *page);
void *frame_evict (void);
void *frame_free (void *kpage);

#endif
