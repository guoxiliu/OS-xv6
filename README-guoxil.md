# Advanced Operating System
## Project 1

### Changes
#### System Call
- add struct definition and function prototype in `defs.h`
- add new system call in `syscall.h` and `syscall.c`
- implement `procinfo` struct in `proc.h`
- implement `getprocsinfo` function in `proc.c`
- implement `sys_getprocsinfo` function in `sysproc.c`

#### Test Function
- add `getprocsinfo` function in `user.h`
- create user test program `testgetprocsinfo.c`
- edit `Makefile` to compile new user program


### How to Run
1. Run `make` in the command line to compile the system kernel.
2. Run `make qemu` in the command line to run qemu emulator.
3. Run `./testgetprocsinfo` in the shell, and it will print out results of three test cases.

#### Optional
To make the program print out information of current processes, simply change `flag` to `1` in `sys_getprocsinfo` function in `sysproc.c` file 


### Explanation
The new added system call is just looking for current used processes in the ptable, so it won't add significant overhead to the existing kernel.
