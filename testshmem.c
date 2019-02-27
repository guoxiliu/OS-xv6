/**
 * Shared Memory Test
 * 	   Guoxi Liu
 */ 
#include "types.h"
#include "user.h"

int
main(int argc, char * argv[]) 
{
    printf(1, "Test accessing shared page 3\n");
    int* ptr1 = (int*) shmem_access(3);
    printf(1, "0x%x: %d [expected = 0x7FFFC000: 0]\n", ptr1, *ptr1);
	
	printf(1, "\nTest accessing shared page 1\n");	
	int* ptr2 = (int*) shmem_access(1);
	*ptr2 = 111;
	printf(1, "0x%x: %d [expected = 0x7FFFE000: 111]\n", ptr2, *ptr2);
	
	printf(1, "\nTest accessing shared page 3\n");
	int* ptr3 = (int*) shmem_access(3);
	printf(1, "0x%x: %d [expected = 0x7FFFC000: 0]\n", ptr3, *ptr3);

	printf(1, "\nTest accessing invalid shared page 4\n");
	int* ptr4 = (int*) shmem_access(4);
	printf(1, "0x%x [expected = 0xFFFFFFFF]\n", ptr4);

	printf(1, "\nTest the counter of valid shared pages\n");
	for (int i = 0; i < 4; i++) {
		printf(1, "%d ", shmem_count(i));
	}
	printf(1, "[expected = 0 1 0 1]\n");

	printf(1, "\nTest the counter of invalid shared page 4\n");
	printf(1, "%d [expected = -1]\n", shmem_count(4));


	// Create one child process to test sharing property.
	int res = fork();
	if (res < 0) {
		printf(1, "fork failed!\n");
	} else if (res == 0) {		
		int* ptr5 = (int*) shmem_access(1);
		printf(1, "\nTest accessing shared page 1 (child process)\n");	
		printf(1, "0x%x: %d [expected = 0x7FFFE000: 111]\n", ptr5, *ptr5);

		int *ptr6 = (int*) shmem_access(2);
		*ptr6 = 222;
		printf(1, "\nTest accessing shared page 2 (child process)\n");	
		printf(1, "0x%x: %d [expected = 0x7FFFD000: 222]\n", ptr6, *ptr6);
		
		printf(1, "\nTest the counter of valid shared pages (child process)\n");
		for (int i = 0; i < 4; i++) {
			printf(1, "%d ", shmem_count(i));
		}
		printf(1, "[expected = 0 2 1 2]\n");
		// exit();

	} else {
		wait();
		int * ptr6 = (int*) shmem_access(2);
		printf(1, "\nTest accessing shared page 2\n");	
		printf(1, "0x%x: %d [expected = 0x7FFFD000: 222]\n", ptr6, *ptr6);
	}

    exit();
}
