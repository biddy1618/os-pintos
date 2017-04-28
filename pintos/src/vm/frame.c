#include "filesys/file.h"
#include "threads/malloc.h"
#include "threads/palloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "vm/frame.h"
#include "vm/page.h"

/* Basic initialization for frame allocation and
   eviction system. */
void frame_table_init (void)
{
	list_init (&frame_table);
	lock_init (&frame_table_lock);
}

/* Function for allocation new frame. */
void *frame_alloc (enum palloc_flags flags, struct sup_page_entry *spte)
{
	/* Try to get the page according to given flags. */
	void *frame = palloc_get_page (flags);

	/* If allocation of page failed, try to evict frame from page
	   table. */
	while (!frame)
	{
		lock_acquire (&frame_table_lock);
		frame = frame_evict (flags);
		lock_release (&frame_table_lock);
	}

	ASSERT(frame != NULL);

	/* Create new entry for frame, and set variabless. */
	struct frame_entry *fe = malloc (sizeof (struct frame_entry));
	fe->frame = frame;
	fe->spte = spte;
	fe->thread = thread_current();

	/* Add frame to frame table. */
	lock_acquire (&frame_table_lock);
	list_push_back (&frame_table, &fe->elem);
	lock_release (&frame_table_lock);

	return frame;
}

/* Function to free the frame. */
void frame_free (void *frame)
{
	struct list_elem *e;
	struct frame_entry *fte;

	lock_acquire (&frame_table_lock);

	/* For each frame entry. */
	for (e = list_begin (&frame_table); e != list_end (&frame_table);
			e = list_next(e))
	{
		fte = list_entry (e, struct frame_entry, elem);

		/* If page matches free it and allocated resourses. */
		if (fte->frame == frame) 
		{
			list_remove (e);
			free (fte);
			palloc_free_page (frame);
			break;
		}
	}
	lock_release (&frame_table_lock);
}

/* Function for choosing a frame to evict. */
void *frame_evict (enum palloc_flags flags)
{
	/* TODO: finish this function */
	return NULL;
}

