#ifndef VM_FRAME_H
#define VM_FRAME_H

#include "threads/palloc.h"
#include "threads/synch.h"
#include "vm/page.h"
#include <list.h>


/* Lock to synchronize access to frame table. */
struct lock frame_table_lock;

/* List to store frame entries. */
struct list frame_table;

/* Struct for frame entry. */
struct frame_entry 
{
	void *frame;				 	/* Pointer to frame. */
	struct sup_page_entry *spte;	/* Pointer to SPE for additional information. */
	struct list_elem elem;			/* List elem for list frame_table. */
	struct thread *thread;			/* Pointer to thread. */ 
};

void frame_table_init (void);
void *frame_alloc (enum palloc_flags flags, struct sup_page_entry *spte);
void frame_free (void *frame);
void *frame_evict (enum palloc_flags flags);

#endif /* vm/frame.h */
