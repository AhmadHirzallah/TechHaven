#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/wait.h>


int main (int argc, char* argv[])
{
	int id = fork();

	if (id == 0)		// If You are child sleep 1 Second!
		sleep(1);
	printf("Current ID: (%d), Parent ID: (%d)\n", getpid(), getppid());	    // getpid() -> Get process id --- getppid() ->Then get Parent ID 


	int wait_id;
	wait_id = wait(NULL);	//	As Parent Proccess : Wait for Child	
	if(wait_id == -1)
		printf("No children to wait for \n");
	else
		printf("(%d) - Finished execution.\n", wait_id);

	return (0);
}
