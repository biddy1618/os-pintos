#ifndef VM_FRAME_H
#define VM_FRAME_H

#include "threads/palloc.h"
#include "vm/page.h"



/* List entry for frame. */
struct frame_entry
{
	struct list_elem elem;		/* List elem for the frame table list. */
	struct thread *thread;		/* Thread to which this frame is allocated. */
	struct spte *spte;			/* Corresponging SPT entry that is linked to
								   this frame entry. */
};

void frame_init (void);
void *frame_alloc (enum palloc_flags flags, struct spte *page);
void *frame_evict (void);
void *frame_free (void *kpage);

#endif
