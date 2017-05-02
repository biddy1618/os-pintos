#include <list.h>
#include "vm/frame.h"
#include "threads/thread.h"
#include "threads/synch.h"
#include "threads/palloc.h"
#include "threads/malloc.h"


struct list frame_table;	/* Table for holding frame entries. */
struct lock frame_lock;	/* Lock to synchronize operations over frame
							   table, since frame table is available for
							   all user threads. */

/* List entry for frame. */
struct frame_entry
{
	struct list_elem elem;		/* List elem for the frame table list. */
	struct thread *thread;		/* Thread to which this frame is allocated. */
	struct spte *spte;			/* Corresponging SPT entry that is linked to
								   this frame entry. */
};

/* Initialization of frame table for all threads. Should be called in
   thread system initialization function. */
void frame_init (void)
{
	list_init (&frame_table);
	lock_init (&frame_lock);
}

/* Whenever thread asks for page, this function should be involved in.
   Basically, it creates frame entry and links it to Supplementary
   Page Table entry of that virtual address of thread. */
void *frame_alloc (enum palloc_flags flags, struct spte *spte)
{
	/* Allocate page from memory. */
	uint8_t *kpage = palloc_get_page(flags);
	
	struct frame_entry *fe;
	
	/* If allocation failed, then swap the frame from frame table.
	   Since every it is needed to update the status of Supplementary
	   Page Table Entry of evicted frame, there should be some way
	   to update SPTE of that frame, either by passing SPTE, or
	   attaching SPTE pointer to frame entry structure, which will
	   be decided later. TODO: Come up with the way to update SPTE
	   of evicted frame. */
	if (kpage == NULL)
		fe = frame_evict ();
	
	/* Allocate frame entry if no page was allocated from pool. */
	if (kpage != NULL)
		fe = malloc (sizeof (struct frame_entry));

	/* Set link of physical address of SPTE and link the SPTE and frame entry. */
	spte->kpage = kpage;
	fe->thread = thread_current ();
	fe->spte = spte;

	/* Add frame entry to frame table. */
	list_push_back (&frame_table, &fe->elem);

	/* Return frame entry. NOTE: Just guessed return type, for now
	   not sure if we need to return at all. TODO: Come up with proper
	   return. */
	return fe;
}

/* Choose frame to evict frame table, swap it out and return freed
   frame as new frame. */
void *frame_evict (void)
{
	/* TODO: implement. */
	PANIC ("Frame evict not implemented.");
}


