#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>	// usleep
#include <time.h>
#include <sys/wait.h>
/*
	- Rather than going to htop to kill/stop/pause/cont a signal; we can do this in the C program
	- function name is kill() which only sends a signal (not killing but it can terminate of course)
	 	- Which take (pid of parent inorder to (send action) to its child) & 2nd parm is the signal
		- The process (child) which receives the signal will perform the required action.
			- Termination/Pause/...etc
*/
#include <signal.h>	

int main(int argc, char **argv)
{

	(void) argc;
	(void) argv;
	int pid = fork();
	if (pid == -1)
	{
		printf("Error in forking\n\n");
		return (-1);
	}
	if (pid == 0)
	{	//Child
		while (1)
		{
			printf("Some Text --\n\n");
			usleep(50000);
		}
	}
	else
	{
		sleep(1);
		kill(pid, SIGKILL);	//SIGKILL Terminates the Child Process. 
		wait(NULL); 
	}

	return (0);
}