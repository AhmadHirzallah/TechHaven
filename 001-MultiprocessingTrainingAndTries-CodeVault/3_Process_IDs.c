// Every process in the system hasa parent process ID that has launched it 
// Except the process with ID 0 Which is The mainprocess which has launched everything in the system
//We need unistd to use fork function
// Unistd is a linux specific library ; it is only found on linux -- some people do same for windows
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>  // Added header for getpid/getppid/wait()

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	
	int id = fork();
	if (id == 0)
		sleep(1);
	printf("Current ID is: (%d)\nParent ID is: (%d)\n\n\n", getpid(), getppid());
	
	int wait_res = wait(NULL);
	if (wait_res == -1)
		printf("No Children to wait for\n\n");
	else
		printf("(%d) process finished execution!\n\n", wait_res);
	return (0);
}
