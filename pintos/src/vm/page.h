#ifndef VM_PAGE_H
#define VM_PAGE_H


#include <hash.h>
#include "vm/frame.h"


/* Flags for SPT entry. */
enum spte_flags
{
	SPTE_WRITABLE = 001,	/* If writable. */
	SPTE_PINNED = 002,		/* If pinned. */
	SPTE_LOADED = 004		/* If loaded - in memory. */
};

/* Struct for SPT entry for thread. */
struct sup_page_entry
{
	void *uva;				/* User Virtual address associated with 
							   current entry. */

	uint8_t status;			/* Status of current SPT entry - spte_flags. */
	struct file *file;		/* File associated with current entry. */
	size_t offset;			/* Offset for sector of file. */
	size_t read_bytes;		/* Number of bytes written to sector. */
	size_t zero_bytes;		/* Number of bytes that are 0-ed. */

	struct hash_elem elem;	/* Hash elem for current SPT entry in 
							   thread's SPT. */
};

void spt_init (struct hash *spt);
void spt_destroy (struct hash *spt);

bool load_page (struct sup_page_entry *spte);
bool load_file (struct sup_page_entry *spte);
bool spt_add_file (struct file *file, int32_t ofs, uint8_t *upage,
					uint32_t read_bytes, uint32_t zero_bytes,
					bool writable);

struct sup_page_entry *get_spte (void *uva);

#endif /* vm/page.h */
