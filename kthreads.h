#ifndef KTHREADS_H
#define KTHREADS_H

#include "param.h"
#include "x86.h"

#define PGSIZE 4096

typedef struct
{  
  uint locked;       // Is the lock held?
} lock_t;

typedef struct
{
    int pid;
    void* stack;
} kthread_t;

void 
init_lock(lock_t* lock)
{
    lock->locked = 0;
}

// Acquire the lock.
void 
lock_acquire(lock_t* lock)
{
    // The xchg is atomic.
    while (xchg(&lock->locked, 1) != 0);
}

// Release the lock.
void 
lock_release(lock_t* lock)
{
    xchg(&lock->locked, 0);
}

kthread_t 
thread_create(void (*start_routine)(void*), void* arg)
{
    kthread_t k;
    lock_t lock;

    init_lock(&lock);
    lock_acquire(&lock);
    void* stack = malloc(2*PGSIZE);
    // when the stack is not page aligned
    if ((uint)stack % PGSIZE) {
        stack = stack + (PGSIZE - (uint)stack % PGSIZE);
    }
    lock_release(&lock);

    k.pid = clone(start_routine, arg, stack);
    k.stack = stack;
    return k;
}

int 
thread_join(kthread_t k)
{
    int ret;
    lock_t lock;

    init_lock(&lock);
    ret = join(k.pid);
    
    lock_acquire(&lock);
    free(k.stack);
    lock_release(&lock);
    return ret;
}

#endif
