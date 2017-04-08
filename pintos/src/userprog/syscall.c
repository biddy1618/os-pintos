#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

#include "devices/shutdown.h"
#include "userprog/process.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "devices/input.h"

static void syscall_handler (struct intr_frame *);

static int get_arg (void *);
static void sys_exit (int);
static int sys_exec (char *);
static int sys_wait (tid_t);
static bool sys_create (char *, unsigned);
static bool sys_remove (char *);
static int sys_open (char *);
static int sys_filesize (int);
static int sys_read (int, char *, unsigned);
static int sys_write (int, char *, unsigned);
static void sys_seek (int, unsigned);
static unsigned sys_tell (int);
static void sys_close (int);



void
syscall_init (void) 
{
	intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
	/* Get the syscall code. */
	int code = get_arg (f->esp);

	switch (code) {
		case SYS_HALT:
		{
			/* Halt the system. */
			shutdown_power_off ();
			break;
		}
		case SYS_EXIT:
		{	
			/* Get first argument. */
			int status = get_arg (f->esp + WORD_SIZE);
			sys_exit (status);
			break;
		}
		case SYS_EXEC:
		{
			/* Get first argument. */
			char *file_name = (char *) get_arg (f->esp + WORD_SIZE);

			/* I was looking in the for the information as to where save
			   return value from the sys_call. Couldn't find any except
			   in internet. Seems like f->eax is place where we should
			   store the return value. Keep in mind that we should store
			   there the return value as int, right in the memory. NOTE:
			   Read online and found that in IAx32 systems, the return
			   scheme differs based on the return type - integral type or
			   pointer will be stored in eax register | floating-point and
			   structures will be stored in floating point register and on
			   stack correspondigly, but seemingly, we don't have to deal
			   with two latter cases here. So just store the return value
			   in f->eax. */
			f->eax = sys_exec (file_name);
			break;
		}
		case SYS_WAIT:
		{
			/* NOTE: used tid_t instead of pid_t. I don't see any problem
			   that it could cause. */

			/* Get first argument. */
			tid_t tid = get_arg (f->esp + WORD_SIZE);

			f->eax = sys_wait (tid);
			break;
		}
		case SYS_CREATE:
		{
			/* Get arguments. */
			char *file = (char *) get_arg (f->esp + WORD_SIZE);
			unsigned init_size = (unsigned) get_arg (f->esp + WORD_SIZE);

			f->eax = sys_create (file, init_size);
			break;
		}
		case SYS_REMOVE:
		{
			/* Get first argument. */
			char *file = (char *) get_arg (f->esp + WORD_SIZE);
			
			f->eax = sys_remove (file);
			
			break;
		}
		case SYS_OPEN:
		{
			/* Get first argument. */
			char *file = (char *) get_arg (f->esp + WORD_SIZE);
			
			f->eax = sys_open (file);
			break;	
		}
		case SYS_FILESIZE:
		{
			/* Get first argument. */
			int fd = get_arg (f->esp + WORD_SIZE);

			f->eax = sys_filesize (fd);
			break;
		}
		case SYS_READ:
		{
			/* Get arguments. */
			int fd = get_arg (f->esp + WORD_SIZE);
			char *buf = (char *) get_arg (f->esp + 2 * WORD_SIZE);
			unsigned size = (unsigned) get_arg (f->esp + 3 * WORD_SIZE);

			f->eax = sys_read (fd, buf, size);
			break;
		}
		case SYS_WRITE:
		{	
			/* Get arguments. */
			int fd = get_arg (f->esp + WORD_SIZE);
			char *buf =  (char *) get_arg (f->esp + 2 * WORD_SIZE);
			unsigned size = (unsigned) get_arg (f->esp + 3 * WORD_SIZE);

			f->eax = sys_write (fd, buf, size);
			break;
		}
		case SYS_SEEK:
		{
			/* Get arguments. */
			int fd = get_arg (f->esp + WORD_SIZE);
			unsigned pos = (unsigned) get_arg (f->esp + 2 * WORD_SIZE);

			sys_seek (fd, pos);
			break;
		}
		case SYS_TELL:
		{
			/* Get first argument. */
			int fd = get_arg (f->esp + WORD_SIZE);

			f->eax = sys_tell (fd);
			break;
		}
		case SYS_CLOSE:
		{	
			/* Get first argument. */
			int fd = get_arg (f->esp + WORD_SIZE);

			sys_close (fd);
			break;
		}
		// case SYS_MMAP:
		// {
		// 	break;
		// }
		// case SYS_MUNMAP:
		// {
		// 	break;
		// }
		// case SYS_CHDIR:
		// {
		// 	break;
		// }
		// case SYS_MKDIR:
		// {
		// 	break;
		// }         
		// case SYS_READDIR:
		// {
		// 	break;
		// }         
		// case SYS_ISDIR:
		// {
		// 	break;
		// }
		// case SYS_INUMBER:
		// {
		// 	break;
		// }
	} 

}

/* Get the value from stack that is placed as size of integer. */
int
get_arg (void *esp)
{
	return *((int *) esp);
}

/* Function that is called when SYS_EXIT invoked. Exits current thread.
   If parent waits for the thread, status will be returned to parent. */ 
void 
sys_exit (int status)
{
	/* Print exit message. */
	printf ("%s: exit(%d)\n", thread_name (), status);
	set_status (status);
	// printf("finish\n");
	thread_exit ();
}

/* Function that is called when SYS_EXEC invoked. Executes given file. */
int
sys_exec (char *file_name) 
{
	/* Execute the command line given. */
	return process_execute (file_name);
}

/* Function that is called when SYS_WAIT invoked. Wait for given process
   to terminate. */
int
sys_wait (tid_t tid)
{	
	/* NOTE: Read 3.3.4 about this system call. */

	/* Wait for the given tid to terminate. */
	return process_wait (tid);
}

/* Function that is called when SYS_CREATE invoked. Create new file with
   initial size of init_size. Returns true, if successful, false
   otherwise. Does not open the file, although creates it. */
bool
sys_create (char *file, unsigned init_size) 
{
	/* TODO: Come up with the file allocation design for the whole
	   project 2. */
	return filesys_create (file, init_size);
}

/* Function that is called when SYS_REMOVE invoked. Deletes the file
   Returns true if successful, false otherwise. File may be removed
   regardless of whether it is open or closed, and removing an open
   file does not close it. */
bool
sys_remove (char *file) 
{
	/* NOTE: Currently, I didn't figure out whether following function
	   somehow affects the file accessibility, if opened by any other
	   threads, so TODO: figure it out in future. */
	return filesys_remove (file);
}
   
/* Function that is called when SYS_OPEN invoked. Returns a file
   descriptor (nonnegative integer), or -1 if file couldn't be opened.
   Shouldn't return 0, or 1, which are reserved for console. */
int
sys_open (char *file)
{
	/* NOTE: Currently, I didn't figure out whether following function
	   somehow affects the file accessibility, if opened by any other
	   threads, so TODO: figure it out in future. */
	
	/* Get the file. */
	struct file *f = filesys_open (file);

	/* TODO: Check the validity of file. */

	/* Add the file as opened file to thread, and return fd. */
	int fd = file_add (f);
	return fd;
}  

/* Function that is called when SYS_FILESIZE invoked. Returns size
   of the file, if this thread owns the file, 0 otherwise. NOTE:
   still do not know whether of current thread doesn't own the file
   descriptor given. */
int
sys_filesize (int fd)
{
	/* Get the opened file by current thread. */
	struct file *f = file_get (fd);

	/* If current thread doesn't own the file, then return 0. */
	if (f == NULL) return -1;

	/* Get the size. */
	int fs = file_length (f);
	return fs;
}

/* Function that is called when SYS_READ invoked. Returns the number
   of bytes actually read. */
int
sys_read (int fd, char *buf, unsigned size)
{
	/* If the read from stdin, then read from keyboard. */
	if (fd == STDIN_FILENO)
	{
		unsigned i;

		/* Create local buffer with uint8_t to map the input_getc
		   function return value. */
		uint8_t *loc = (uint8_t *) buf;
		for (i = 0; i < size; i++) {
			loc[i] = input_getc ();
		}

		/* Return the number of bytes written. */
		return size;
	}

	/* If the read from stdout, then return error. */
	if (fd == STDOUT_FILENO)
	{
		return -1;
	}

	/* Otherwise it is file descriptor. Get the opened file by 
	   current thread. */
	struct file *f = file_get (fd);

	/* If current thread doesn't own the file, then return 0. */
	if (f == NULL) return -1;

	/* Read the file, and return the number of bytes actually read.
	   Might be less than size, if EOF reached. */
	return file_read (f, buf, size);
}



/* Function that is called when SYS_CALL invoked. Returns the number
   of bytes actually written. */
int 
sys_write (int fd, char *buf, unsigned size) 
{
	/* If the write to stdin, then return error. */
	if (fd == STDIN_FILENO)
	{
		return -1;
	}

	/* If output is for console. */ 
	if (fd == STDOUT_FILENO)
	{
		putbuf(buf, size);
		/* TODO: Implement checking for the actually number of bytes
		   written. */
		return (int) size;
	}
	
	/* Otherwise it is file descriptor. Get the opened file by 
	   current thread. */
	struct file *f = file_get (fd);

	/* If current thread doesn't own the file, then return error. */
	if (f == NULL) return -1;

	return file_write (f, buf, size);
}

/* Function that is called when SYS_SEEK invoked. Changes the next
   byte to be read or written in open file fd to position expressed
   in bytes. */
void 
sys_seek (int fd, unsigned pos) 
{
	/* If the file is stdout or stdin, then return error. */
	if (fd == STDIN_FILENO || STDOUT_FILENO)
	{
		return;
	}

	/* Otherwise it is file descriptor. Get the opened file by 
	   current thread. */
	struct file *f = file_get (fd);

	/* If current thread doesn't own the file, then return error. */
	if (f == NULL) return;

	file_seek (f, pos);
}

/* Function that is called when SYS_TELL invoked. Return the
   position of the next byte to be read or written in open file fd,
   expressed in bytes from the beginning of the file. */
unsigned 
sys_tell (int fd) 
{
	/* If the file is stdout or stdin, then return error. */
	if (fd == STDIN_FILENO || STDOUT_FILENO)
	{
		return -1;
	}

	/* Otherwise it is file descriptor. Get the opened file by 
	   current thread. */
	struct file *f = file_get (fd);

	/* If current thread doesn't own the file, then return error. */
	if (f == NULL) return -1;

	return file_tell (f);
}

/* Function that is called when SYS_CLOSE invoked. Closes file
   descriptor fd. */
void
sys_close (int fd) 
{
	/* If the file is stdout or stdin, then return error. */
	if (fd == STDIN_FILENO || STDOUT_FILENO)
	{
		return;
	}

	/* Otherwise it is file descriptor. Remove the file meta
	   struct. */
	struct file *f = file_remove (fd);
	
	/* If failed, then return error. */
	if (f == NULL) return;

	/* If successfull, then close file. */
	file_close (f);
}

