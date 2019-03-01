#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// return the number of existing processes
int
sys_getprocsinfo(void)
{
	int flag = 1;		// whether to print out information 
	struct procinfo procs[NPROC];
	int procs_num = getprocsinfo(procs);
	
	// print out process names
	if (flag) {
		for (int i = 0; i < procs_num; i++) {
			cprintf("%d: %s\n", procs[i].pid, procs[i].pname);
		}
	}

	return procs_num;
}

// return the virtual address space of a shared page
int 
sys_shmem_access(void)
{
  int page_num;
  if (argint(0, &page_num) < 0) {
    return -1;
  }
  return (int)shmem_access(page_num);
}

// return the number of processes that have access to a shared page
int
sys_shmem_count(void)
{
  int page_num;
  if (argint(0, &page_num) < 0) {
    return -1;
  } 
  return shmem_count(page_num);
}

// clone system call for creating the thread
int
sys_clone(void)
{
  void (*fcn)(void*);
  void *arg;
  void *stack;

  if (argptr(0, (void*)&fcn, sizeof(void*)) < 0) {
    return -1;
  }
  if (argptr(1, (void*)&arg, sizeof(void*)) < 0) {
    return -1;
  }
  if (argptr(2, (void*)&stack, sizeof(void*)) < 0) {
    return -1;
  }

  return clone(fcn, arg, stack);
}

// join system call for waiting the child thread
int
sys_join(void)
{
  int pid;
  if (argint(0, &pid) < 0) {
    return -1;
  }
  return join(pid);
}
