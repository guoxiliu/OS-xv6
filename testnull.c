/**
 * NULL Pointer Dereference Test
 * 		Guoxi Liu
 */ 
#include "syscall.h"
#include "types.h"
#include "user.h"

#define NULL 0

int main()
{
	int a;
	int* pi = NULL;
	
	a = *pi;

	printf(1, "%d\n", a);
	
	exit();
}
