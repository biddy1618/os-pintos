#include <string.h>
#include <stdio.h>
#include "vm/page.h"
#include "vm/swap.h"
#include "threads/malloc.h"
#include "threads/vaddr.h"
#include "userprog/process.h"

static unsigned page_hash_func (const struct hash_elem *, 
								void * UNUSED);
static bool page_less_func (const struct hash_elem *, 
							const struct hash_elem *,
							void * UNUSED);
static void page_free_func (struct hash_elem *e,
							void *aux UNUSED);




/* Initialize the hash table that is used as Supplementary Page
   Table. */
void spt_init (void)
{
	hash_init(&thread_current ()->spt, page_hash_func, page_less_func, NULL);
}

/* Create virtual page that starts at address given as uaddr. */
void *create_page (void *uaddr, enum palloc_flags flags, enum spte_flags status)
{
	// printf("created page with p %p in thread %s\n", uaddr, thread_name ());
	struct spte *page = malloc (sizeof (struct spte));
	page->upage = uaddr;
	page->flags = flags;
	page->status = status;
	page->fe = NULL;
	page->swap_idx = LOADED;
	// page->file = NULL;
	// page->ofs = 0;
	// page->read_bytes = 0;
	// page->zero_bytes = 0;

	hash_insert (&thread_current ()->spt, &page->elem);

	return page;
}

/* Search for SPT entry that of given user virtual address.
   If there is a page with that address, return SPTE. Otherwise
   return NULL. */
struct spte *get_page (void *uaddr)
{
	struct spte spte;

	/* Allign the pointer with paging. */
	spte.upage = pg_round_down (uaddr);
	
	/* Try to find the STP entry corresponding to the uaddr. */
	struct hash_elem *he = hash_find (&thread_current ()->spt, 
										&spte.elem);

	/* If the page was found, return the page, otherwise NULL. */
	return he == NULL ? NULL : hash_entry (he, struct spte, elem);
}

/* Load page. */
bool load_page (struct spte *spte)
{
	/* Set the status of page as pinned, so that the frame 
	   associated is not candidate for eviction when other
	   processes request for frame eviction. */
	spte->status |= PINNED;

	/* Allocate a frame for current SPTE. */
	struct frame_entry *fe = frame_alloc(spte);

	// printf("allocating frame for page %p with fe %p\n", spte, fe);
	if (!fe)
		return false;

	/* If page is in swap area, then load it. */
	if (spte->swap_idx != LOADED)
	{
		// printf("loading page from swap\n");
		swap_in (spte);
	}

	/* If page is associated with file, then load the file into
	   memory. */
	// if (spte->status & FILE)
	// {
	// 	/* NOTE: do we need to lock the filesys_lock? */
	// 	if (file_read_at (spte->file, 
	// 					fe->kpage, 
	// 					spte->read_bytes, 
	// 					spte->ofs) != (int) spte->read_bytes)
	// 	{
	// 		free_page (spte);
	// 		return false;
	// 	}
	// 	memset (fe->kpage + spte->read_bytes, 0, spte->zero_bytes);
	// }

	spte->status &= ~PINNED;

	if (spte->upage == (void *) 0xbffff000)
	{
		bool heu = install_page (spte->upage, 
						fe->kpage, 
						spte->status & WRITABLE);
		// printf("Writable %d\n", spte->status & WRITABLE);
		// hex_dump (spte->upage, fe->kpage, PGSIZE, true);
		// printf("CHECK %p\n", *((void **) 0xbffffdd0));
		return heu;
	}

	return install_page (spte->upage, 
						fe->kpage, 
						spte->status & WRITABLE);
}

/* Free page and associated memory with it. */
void free_page (struct spte *spte)
{
	/* In the process exit, the pagedir_destroy(...) actually deallocates
	   all the pages linked to current process, so there is no need to
	   manually deallocate all the pages, just need to set bits in swap
	   bitmap so that it is available for other processes. */
	if (spte->swap_idx == LOADED)
	{
		ASSERT (spte->fe != NULL);
		// printf("removing frame %p from frames in thread %s\n", spte->fe->kpage, thread_name ());
		// if (spte->fe->kpage == (void *) 0xc038d000)
  //             printf("LOL\n");
            
		frame_free (spte->fe);
	}
	else
	{
		swap_free (spte->swap_idx);
	}
	free (spte);	
}

void spt_destroy (void)
{
	hash_destroy (&thread_current ()->spt, page_free_func);
}

/* Hash function for Supplementary Page Table. */
static unsigned page_hash_func (const struct hash_elem *e, 
								void *aux UNUSED)
{
	struct spte *page = hash_entry (e, struct spte, elem);

	return hash_bytes (&page->upage, sizeof (page->upage));
}

/* Comparison function for Hash Table (SPT). */
static bool page_less_func (const struct hash_elem *a, 
							const struct hash_elem *b,
							void *aux UNUSED)
{
	struct spte *sa = hash_entry(a, struct spte, elem);
	struct spte *sb = hash_entry(b, struct spte, elem);

	return sa->upage < sb->upage;
}

static void page_free_func (struct hash_elem *e,
								void *aux UNUSED)
{
	struct spte *s = hash_entry (e, struct spte, elem);
	free_page (s);
}

