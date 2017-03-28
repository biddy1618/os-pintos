/* This file is derived from source code for the Nachos
   instructional operating system.  The Nachos copyright notice
   is reproduced in full below. */

/* Copyright (c) 1992-1996 The Regents of the University of California.
   All rights reserved.

   Permission to use, copy, modify, and distribute this software
   and its documentation for any purpose, without fee, and
   without written agreement is hereby granted, provided that the
   above copyright notice and the following two paragraphs appear
   in all copies of this software.

   IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO
   ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR
   CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OF THIS SOFTWARE
   AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF CALIFORNIA
   HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
   PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS"
   BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO
   PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
   MODIFICATIONS.
*/

#include "threads/synch.h"
#include <stdio.h>
#include <string.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void priority_donate (struct thread *);

/* Initializes semaphore SEMA to VALUE.  A semaphore is a
   nonnegative integer along with two atomic operators for
   manipulating it:

   - down or "P": wait for the value to become positive, then
     decrement it.

   - up or "V": increment the value (and wake up one waiting
     thread, if any). */
void
sema_init (struct semaphore *sema, unsigned value) 
{
  ASSERT (sema != NULL);

  sema->value = value;
  list_init (&sema->waiters);
}

/* Down or "P" operation on a semaphore.  Waits for SEMA's value
   to become positive and then atomically decrements it.

   This function may sleep, so it must not be called within an
   interrupt handler.  This function may be called with
   interrupts disabled, but if it sleeps then the next scheduled
   thread will probably turn interrupts back on. This is
   sema_down function. */
void
sema_down (struct semaphore *sema) 
{
  enum intr_level old_level;

  ASSERT (sema != NULL);
  ASSERT (!intr_context ());

  old_level = intr_disable ();
  while (sema->value == 0) 
  {
    /* Insert the waiting thread to wait list sorted by priority. */
    list_insert_ordered (&sema->waiters, &thread_current ()->elem, 
                        (list_less_func *) compare_priority, NULL);
    thread_block ();
  }
  sema->value--;
  intr_set_level (old_level);
}

/* Down or "P" operation on a semaphore, but only if the
   semaphore is not already 0.  Returns true if the semaphore is
   decremented, false otherwise.

   This function may be called from an interrupt handler. */
bool
sema_try_down (struct semaphore *sema) 
{
  enum intr_level old_level;
  bool success;

  ASSERT (sema != NULL);

  old_level = intr_disable ();
  if (sema->value > 0) 
    {
      sema->value--;
      success = true; 
    }
  else
    success = false;
  intr_set_level (old_level);

  return success;
}

/* Up or "V" operation on a semaphore.  Increments SEMA's value
   and wakes up one thread of those waiting for SEMA, if any.

   This function may be called from an interrupt handler. */
void
sema_up (struct semaphore *sema) 
{
  enum intr_level old_level;

  ASSERT (sema != NULL);

  old_level = intr_disable ();
  if (!list_empty (&sema->waiters)) 
  {
    /* If waiters list is not empty, pop up the first thread,
       since they are sorted according to priority. */
    list_sort(&sema->waiters, 
              (list_less_func *) compare_priority, 
              NULL);
    struct thread *t = list_entry (
                            list_pop_front (&sema->waiters),
                            struct thread, elem); 
    thread_unblock (t);
  }
  sema->value++;
  /* After unblocking thread, yield current thread in case
     unblocked thread had a higher priority. */
  thread_yield ();
  intr_set_level (old_level);
}

static void sema_test_helper (void *sema_);

/* Self-test for semaphores that makes control "ping-pong"
   between a pair of threads.  Insert calls to printf() to see
   what's going on. */
void
sema_self_test (void) 
{
  struct semaphore sema[2];
  int i;

  printf ("Testing semaphores...");
  sema_init (&sema[0], 0);
  sema_init (&sema[1], 0);
  thread_create ("sema-test", PRI_DEFAULT, sema_test_helper, &sema);
  for (i = 0; i < 10; i++) 
    {
      sema_up (&sema[0]);
      sema_down (&sema[1]);
    }
  printf ("done.\n");
}

/* Thread function used by sema_self_test(). */
static void
sema_test_helper (void *sema_) 
{
  struct semaphore *sema = sema_;
  int i;

  for (i = 0; i < 10; i++) 
    {
      sema_down (&sema[0]);
      sema_up (&sema[1]);
    }
}

/* Initializes LOCK.  A lock can be held by at most a single
   thread at any given time.  Our locks are not "recursive", that
   is, it is an error for the thread currently holding a lock to
   try to acquire that lock.

   A lock is a specialization of a semaphore with an initial
   value of 1.  The difference between a lock and such a
   semaphore is twofold.  First, a semaphore can have a value
   greater than 1, but a lock can only be owned by a single
   thread at a time.  Second, a semaphore does not have an owner,
   meaning that one thread can "down" the semaphore and then
   another one "up" it, but with a lock the same thread must both
   acquire and release it.  When these restrictions prove
   onerous, it's a good sign that a semaphore should be used,
   instead of a lock. */
void
lock_init (struct lock *lock)
{
  ASSERT (lock != NULL);

  lock->holder = NULL;
  sema_init (&lock->semaphore, 1);
}

/* Function that donates current thread's priority to lock
   holder, if necessary, does it for other layers as well. */ 
static void
priority_donate (struct thread *t)
{
  int new_priority = t->priority;
  struct lock *l = t->lock;

  // /* Traverse the list of all held locks for thread t and
  //    pick the highest priority among holders. */
  // struct list_elem *elem = list_begin(&t->locks); 
  // struct thread *temp;
  // struct list *wait_threads;
  // while (elem != list_end (&t->locks))
  // {
  //   wait_threads = &(list_entry (elem, struct lock, elem)
  //                                   ->semaphore.waiters);
  //   /* Check the priority of the first thread waiting for 
  //      a lock. Since the list is sorted, the first one is 
  //      supposed to have the highest priority. */
  //   if (!list_empty (wait_threads) && 
  //     (temp = list_entry (list_front (wait_threads), 
  //     struct thread, elem))->priority > new_priority)
  //   {
  //     new_priority = temp->priority;
  //   }
  //   elem = list_next(elem);
  // }

  /* Update the priorities of the thread that is holder
     of the current lock, and check if it is waiting for
     other thread, and if so, update it too, and continue
     in that manner. */
  while (l != NULL && l->holder != NULL)
  {
    if (l->holder->priority < new_priority)
    {
      l->holder->priority = new_priority;
    }

    /* Check the next level, and if necessary, update the
       next thread's waiting lock's holder's priority. */
    l = l->holder->lock;
  }
  /* Set highest priority. */
  t->priority = new_priority;
}

/* Acquires LOCK, sleeping until it becomes available if
   necessary.  The lock must not already be held by the current
   thread.

   This function may sleep, so it must not be called within an
   interrupt handler.  This function may be called with
   interrupts disabled, but interrupts will be turned back on if
   we need to sleep. */
void
lock_acquire (struct lock *lock)
{
  ASSERT (lock != NULL);
  ASSERT (!intr_context ());
  ASSERT (!lock_held_by_current_thread (lock)); 

  enum intr_level old_level;
  ASSERT (!intr_context ());
  old_level = intr_disable ();  
  
  /* Try to down the semaphore. */
  if (!sema_try_down (&lock->semaphore)) 
  {
    thread_current ()->lock = lock;
    /* If unsuccessful, then, if current thread's priority is
       higher, then donate. Otherwise just put in the wait list
       and block. */
    if (thread_get_priority () > lock->holder->priority)
    {
       priority_donate (thread_current ()); 
    }
    sema_down (&lock->semaphore);
    /* Since the thread acquaired the lock, set the waiting
       lock to NULL. */
    thread_current ()->lock = NULL;
  }
  /* Update the list of lock holders and add the lock
     into the list of locks current thread has acquared. */
  lock->holder = thread_current ();
  list_push_back(&thread_current ()->locks, &lock->elem);
  intr_set_level (old_level);
}

/* Tries to acquire LOCK and returns true if successful or false
   on failure.  The lock must not already be held by the current
   thread.

   This function will not sleep, so it may be called within an
   interrupt handler. */
bool
lock_try_acquire (struct lock *lock)
{
  bool success;

  ASSERT (lock != NULL);
  ASSERT (!lock_held_by_current_thread (lock));

  success = sema_try_down (&lock->semaphore);
  if (success)
    lock->holder = thread_current ();
  return success;
}

/* Releases LOCK, which must be owned by the current thread.
   This is lock_release function.

   An interrupt handler cannot acquire a lock, so it does not
   make sense to try to release a lock within an interrupt
   handler. */
void
lock_release (struct lock *lock) 
{
  ASSERT (lock != NULL);
  ASSERT (lock_held_by_current_thread (lock));

  enum intr_level old_level;
  ASSERT (!intr_context ());
  old_level = intr_disable ();

  lock->holder = NULL;

  /* Release the lock from list of acquaired locks. */
  if (!list_empty (&lock->elem) )
  {
    list_remove (&lock->elem);
  }
  
  /* Change the priority of current thread to the highest
     priority of the threads that are waiting on the lock
     current thread releasing, if such doesn't exist, then
     set the priority to the initial priority of the thread. */
  int new_priority = thread_current ()-> priority_init;
  struct list_elem *list_el = list_begin (&thread_current ()->locks);
  struct thread *temp;
  struct list *wait_threads;
  /* Iterate over all locks current thread possessing. */
  while (list_el != list_end (&thread_current ()->locks))
  {
    wait_threads = &(list_entry (list_el, struct lock, elem)
                                        ->semaphore.waiters);
    /* Check the priority of the first thread waiting for a lock.
       Since the list is sorted, the first one is supposed
       to have the highest priority. */
    if (!list_empty (wait_threads) && 
      (temp = list_entry (list_front (wait_threads), 
      struct thread, elem))->priority > new_priority)
    {
      new_priority = temp->priority;
    }

    list_el = list_next (list_el);
  }
  thread_current ()->priority = new_priority;


  /* Up the semaphore and thread yield in case the unblocked
     thread has high priority .*/
  sema_up (&lock->semaphore);
  thread_yield ();
  intr_set_level (old_level);
}

/* Returns true if the current thread holds LOCK, false
   otherwise.  (Note that testing whether some other thread holds
   a lock would be racy.) */
bool
lock_held_by_current_thread (const struct lock *lock) 
{
  ASSERT (lock != NULL);

  return lock->holder == thread_current ();
}

/* One semaphore in a list. */
struct semaphore_elem 
  {
    struct list_elem elem;              /* List element. */
    struct semaphore semaphore;         /* This semaphore. */
  };

/* Initializes condition variable COND.  A condition variable
   allows one piece of code to signal a condition and cooperating
   code to receive the signal and act upon it. */
void
cond_init (struct condition *cond)
{
  ASSERT (cond != NULL);

  list_init (&cond->waiters);
}

/* Atomically releases LOCK and waits for COND to be signaled by
   some other piece of code.  After COND is signaled, LOCK is
   reacquired before returning.  LOCK must be held before calling
   this function.

   The monitor implemented by this function is "Mesa" style, not
   "Hoare" style, that is, sending and receiving a signal are not
   an atomic operation.  Thus, typically the caller must recheck
   the condition after the wait completes and, if necessary, wait
   again.

   A given condition variable is associated with only a single
   lock, but one lock may be associated with any number of
   condition variables.  That is, there is a one-to-many mapping
   from locks to condition variables.

   This function may sleep, so it must not be called within an
   interrupt handler.  This function may be called with
   interrupts disabled, but interrupts will be turned back on if
   we need to sleep. */
void
cond_wait (struct condition *cond, struct lock *lock) 
{
  struct semaphore_elem waiter;

  ASSERT (cond != NULL);
  ASSERT (lock != NULL);
  ASSERT (!intr_context ());
  ASSERT (lock_held_by_current_thread (lock));
  
  sema_init (&waiter.semaphore, 0);
  list_push_back (&cond->waiters, &waiter.elem);
  lock_release (lock);
  sema_down (&waiter.semaphore);
  lock_acquire (lock);
}

/* If any threads are waiting on COND (protected by LOCK), then
   this function signals one of them to wake up from its wait.
   LOCK must be held before calling this function.

   An interrupt handler cannot acquire a lock, so it does not
   make sense to try to signal a condition variable within an
   interrupt handler. */
void
cond_signal (struct condition *cond, struct lock *lock UNUSED) 
{
  ASSERT (cond != NULL);
  ASSERT (lock != NULL);
  ASSERT (!intr_context ());
  ASSERT (lock_held_by_current_thread (lock));

  if (!list_empty (&cond->waiters))
  {
    sema_up (&list_entry (list_pop_front (&cond->waiters),
                  struct semaphore_elem, elem)->semaphore);
  }
}

/* Wakes up all threads, if any, waiting on COND (protected by
   LOCK).  LOCK must be held before calling this function.

   An interrupt handler cannot acquire a lock, so it does not
   make sense to try to signal a condition variable within an
   interrupt handler. */
void
cond_broadcast (struct condition *cond, struct lock *lock) 
{
  ASSERT (cond != NULL);
  ASSERT (lock != NULL);

  while (!list_empty (&cond->waiters))
    cond_signal (cond, lock);
}
