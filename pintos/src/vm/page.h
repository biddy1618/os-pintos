#ifndef VM_PAGE_H
#define VM_PAGE_H

#include "threads/thread.h"
#include "vm/frame.h"

typedef uint8_t spte_flags;

#define SPTE_SWAPPED = 0x1

/* SPT entry. */
struct spte
{
	void *upage;				/* Virtual address of process page. */
	void *kpage;				/* Physical address of process page, if it
								   is linked to any. */
	spte_flags flags;			/* Flags, like swap, or anything. */
	struct frame_entry *fe;		/* Frame entry to whic SPTE is linked to, 
								   if any. */
	struct hash_elem elem;		/* Hash element to manipulate hash SPT. */
};

void spt_init (struct thread *t);
void* create_page (void *uaddr);
bool load_page (void *uaddr);
bool swap_page (void *uaddr);

#endif
