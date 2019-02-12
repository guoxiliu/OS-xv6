#include "types.h"
#include "user.h"
#include "syscall.h"

int stdout = 1;

// Create a new process using fork() function.
void 
newProcess()
{
	int rc = fork();
	// the child process
	if (rc == 0) {
		sleep(2);
		exit();
	} 

	/* This is for parent process */
	/* Leave it commented for testing purpose! */
	// else if (rc > 0) {
		// wait();		// wait for child process to exit
	// }

}

int
main(int argc, char *argv[])
{
	printf(stdout, "Testing getprocsinfo...\n");

	// Test 1
	printf(stdout, "TEST1: %d\n\n", getprocsinfo());

	// Test 2
	for (int i = 0; i < 3; i++) {
		newProcess();
	}
	printf(stdout, "TEST2: %d\n\n", getprocsinfo());

	// Test 3
	for (int i = 0; i < 2; i++) {
		newProcess();
	}
	printf(stdout, "TEST3: %d\n\n", getprocsinfo());
	
	exit();
}
