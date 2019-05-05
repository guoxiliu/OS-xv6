# Advanced Operating Systems
## Project 3

### Kernel Thread
For this project, we need to make xv6 support kernel threads. To do this, we have two system calls: `clone` and `join`. 

#### System Calls 
- Add system calls of clone and join for xv6. This involves `defs.h`, `syscall.h`, `syscall.c`, `sysproc.c`, `usys.S`.
- Add a field into `struct proc` in `proc.h` (i.e., `is_thread`) which tells if the process is a thread or not. 
- Implement `clone()` function, which is similar to `fork()`, but there is no need to allocate new memory space for the thread. Beside, `is_thread` should be set to `1` for thread and the stack of the thread should store the passing argument and a fake return address `0xffffffff`. Several registers also need to be updated, like `eax`, `esp`, `esi`, `ebp`.
- Implement `join()` function, which is similar to `wait()`. The only difference is that we only search threads in the process table and will not clear the memory space of the thread.
- Modify the existing system calls. In `allocproc()` we will set `is_thread` to `0` first; In `growproc()` we need to make sure threads have the same memory size with the parent; In `exit()` we should check if current element of process table is a thread or not; Since `wait()` is used for processes, we will skip threads when we search the process table. 
- One small issue is with `argptr()`, the line `if (i < PGSIZE)` should be removed for the tests to work properly. (It would be fine unless we do not dereference the pointer).

#### Thread Library
There are two functions provided for threads: `thread_create()` and `thread_join()`. In `thread_create()`, the stack need to be allocated before calling the `clone()` function, and in `thread_join()` the space need to be deallocated. To make them thread safe, a spinlock will be implemented as well.

### Tests
There are two test files in this project, one is `simple_threads.c`, and the other is `testkthreads.c`. To use them, just run `simple_thread` and `testkthreads` in the qemu.