#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>

int main (int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;

	int pid = fork();
	if (pid == -1)
	{
		printf("Fork Error\n");
		return (1);
	}
	if (pid == 0)
	{// Child Process
		char *arr[]  = {"ping", "-c", "3", "Google.com", NULL};
		// Child Process get overridden/replaced by the ping process.
		execve("/bin/ping", arr, envp);
		printf("THIS SHOULDN'T PRINT ON THE TERMINAL\n\n");
	}
	else
	{// Parent Process
		// Waiting after the child process (pid == 0) finish (finishing execv) then Parent will be executed
		wait(NULL);	
		//Post Processing; we can for example create a file to store the data//Create Fifo
		printf("\nSomething After execve (Post Processing is happening).\t\t<<<<<<<<--------------------\n\n");
	}

	return (0);
}