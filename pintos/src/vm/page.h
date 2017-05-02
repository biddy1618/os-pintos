#ifndef VM_PAGE_H
#define VM_PAGE_H

#include "threads/thread.h"

typedef uint8_t spte_flags;

#define SPTE_SWAPPED = 0x1

struct spte
{
	void *upage;
	void *kpage;
	spte_flags flags;
	struct hash_elem elem;
};

void spt_init (struct thread *t);
void* create_page (void *uaddr);
bool load_page (void *uaddr);
bool swap_page (void *uaddr);

#endif
