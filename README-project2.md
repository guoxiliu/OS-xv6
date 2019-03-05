# Advanced Operating System
## Project 2

### Part A: Null-Pointer Dereference 
For this part, my idea was just to make the address 0 inaccessible. To achieve this, I made following changes:
- change `sz = PGSIZE` in `exec.c`
- change the for loop to start from `PGSIZE` in `fork()` (actually `cpuvm()` to be specific)
- change the for loop to start from `4096` in `usertest.c` (which is for validate test)
- set the entry point to be `0x1000` instead of `0` in `Makefile`

### Part B: Shared Pages
For this part, my idea was to initialize shared memory when booting and use two arrays to keep track of both references and address of the shared memory. Besides, each process has its own counters and virtual address for shared memory. Below is what I have done for this part: 
- add system calls for shared pages like last project (i.e., `shmem_access` and `shmem_count`)
- create a new function called `shmeminit()` which calls `kalloc()` to allocate shared memory space in `main.c`
- deallocate only non-shared memory for each process in `freevm()` 
- change `copyuvm()` to make the shared memory work for `fork()`
- map the virtual address to the physical memory in `shmem_access()` 
- decrement the counter of shared pages when the process exits
- do some boundary checking in memory allocation and instruction fetching

### Testing
The two programs for testing part A and part B of the project are called `testnull` and `testshmem` respectively. To test the project, just run `./testnull` or `./testshmem` in the qemu.

The output for `testshmem` may be a little bit longer, however, you can still view it in the terminal instead of qemu.