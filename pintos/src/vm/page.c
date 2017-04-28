#include <string.h>
#include "filesys/file.h"
#include "threads/interrupt.h"
#include "threads/malloc.h"
#include "threads/palloc.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "userprog/pagedir.h"
#include "userprog/syscall.h"
#include "userprog/process.h"
#include "vm/frame.h"
#include "vm/page.h"

static unsigned page_hash_func (const struct hash_elem *e, void *aux UNUSED);
static void page_action_func (struct hash_elem *e, void *aux UNUSED);
static bool page_less_func (const struct hash_elem *a,
			const struct hash_elem *b, void *aux UNUSED);

/* Initialization of Supplementary Page Table. */
void spt_init (struct hash *spt)
{
	hash_init (spt, page_hash_func, page_less_func, NULL);
}

/* Function that deallocates SPT of current thread. */
void spt_destroy (struct hash *spt)
{
	hash_destroy (spt, page_action_func);
}

struct sup_page_entry *get_spte (void *uva)
{
	struct sup_page_entry spte;

	/* Round down given User Virtual address so that it is alligned. */
	spte.uva = pg_round_down (uva);

	struct hash_elem *e = hash_find (&thread_current ()->spt, &spte.elem);
	if (e == NULL) return NULL;
	return hash_entry (e, struct sup_page_entry, elem);
}

/* Function that loads page if it is not installed onto current virtual
   address of process. */
bool load_page (struct sup_page_entry *spte)
{
	bool success = load_file (spte);

	return success;
}

/* Load a page with file. */
bool load_file (struct sup_page_entry *spte)
{
	/* Allocate page from user pool. */
	enum palloc_flags flags = PAL_USER;

	/* If read bytes are 0, then set the page to zero. */
	if (spte->read_bytes == 0)
		flags |= PAL_ZERO;

	/* Allocate frame which allocates a page. */
	void *frame = frame_alloc (flags, spte);
	if (!frame) 
		return false;

	/* If write is more than 0, then write file contents to
	   page. */
	if (spte->read_bytes > 0)
	{
		lock_acquire (&filesys_lock);

		/* Make sure that read bytes are equal to actual
		   number of bytes read from file. */
		if ((int) spte->read_bytes != file_read_at (
			spte->file, frame,
			spte->read_bytes,
			spte->offset))
		{
			lock_release (&filesys_lock);
			frame_free (frame);
			return false;
		}

		lock_release (&filesys_lock);
		memset(frame + spte->read_bytes, 0, spte->zero_bytes);
	}

	/* Map the virtual address of page of process to match the
	   physical frame. */
	if (!install_page (spte->uva, frame, spte->status & SPTE_WRITABLE))
	{
		frame_free (frame);
		return false;
	}

	return true;
}

/* Adds a new file to SPT and return true, if no such was found
   in the table with User Page upage, otherwise false. */
bool spt_add_file (struct file *file, int32_t ofs, uint8_t *upage,
					uint32_t read_bytes, uint32_t zero_bytes,
					bool writable)
{
	struct sup_page_entry *spte = malloc (sizeof (struct sup_page_entry));
	spte->file = file;
	spte->offset = ofs;
	spte->uva = upage;
	spte->read_bytes = read_bytes;
	spte->zero_bytes = zero_bytes;
	spte->status = writable & SPTE_WRITABLE;

	return (hash_insert (&thread_current ()->spt, &spte->elem) == NULL);
}

/* SPT hash function. */
unsigned page_hash_func (const struct hash_elem *e, void *aux UNUSED)
{
	struct sup_page_entry *spte = hash_entry (e, 
				struct sup_page_entry, elem);
	return hash_int ((int) spte->uva);
}

/* Comparison function for hash table. */
bool page_less_func (const struct hash_elem *a,
			const struct hash_elem *b, void *aux UNUSED)
{
	struct sup_page_entry *sa = hash_entry (a,
			struct sup_page_entry, elem);
	struct sup_page_entry *sb = hash_entry (b,
			struct sup_page_entry, elem);

	return sa->uva < sb->uva;
}

/* Deallocation function for hash destroy function. */
void page_action_func (struct hash_elem *e, void *aux UNUSED)
{
	struct sup_page_entry *spte = hash_entry (e,
			struct sup_page_entry, elem);

	/* If SPT entry is loaded, then clear the page from pagedir. */
	if (spte->status & SPTE_LOADED)
	{
		frame_free (pagedir_get_page (thread_current ()->pagedir, spte->uva));
		pagedir_clear_page (thread_current ()->pagedir, spte->uva);
	}
	free (spte);
}
