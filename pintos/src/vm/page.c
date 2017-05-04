#include "vm/page.h"
#include "threads/malloc.h"

static unsigned page_hash_func (const struct hash_elem *, void * UNUSED);
static bool page_less_func (const struct hash_elem *, 
							const struct hash_elem *,
							void * UNUSED);




/* Initialize the hash table that is used as Supplementary Page
   Table. */
void spt_init (struct thread *t)
{
	hash_init(&t->spt, page_hash_func, page_less_func, NULL);
}

/* Create virtual page that starts at address given as uaddr. */
void *create_page (void *uaddr)
{
	struct spte *page = malloc (sizeof (struct spte));
	page->upage = uaddr;
	page->kpage = NULL;
	page->flags = 0;

	hash_insert (&thread_current ()->spt, &page->elem);

	return page;
}

/* Hash function for Supplementary Page Table. */
static unsigned page_hash_func (const struct hash_elem *e, void *aux UNUSED)
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



