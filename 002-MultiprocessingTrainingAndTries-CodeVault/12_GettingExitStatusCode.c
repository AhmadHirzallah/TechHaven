#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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
	/*
		-	 Our purpose is to check if the program itself Succeeded executing;
			OR the program Failed in executing and we have some errors.
		- There is many types of errors (we will list 2):
			1. if the ping program does not exist is not found
			2. if the actual ping program is found and executed 
				but it gives out an error
		- how can we treat each of the error types: 
			- exec functions replace all the code and all the memory of our current process;
				 only if it's successful in finding the program that it needs to execute
				 and so on and so forth 
			- if it doesn't find it if something's wrong with the name of the program;
				 then it does in fact not replace the process (code) and it continues its execution
		- exec function return int to indicate it succeed or failed 
			- if it returns (-1) : 
				- there is an error in finding or launching the program! 
				- and execve will fail !
		- The wait(NULL); takes an int pointer ; it tell us info about child waited process !
	*/
	if (pid == 0)
	{
		// Child Process
		char *arr[]  = {"ping", "-c", "3", "Google.com", NULL};
		int err = execve("/bin/ping", arr, envp);	// THIS WILL WORK
		// int err = execve("/bin/pingr", arr, envp);	// THIS WON'T WORK
		// char *arr_err[]  = {"ping", "-c", "3", "Google.commamam", NULL};
		// int err = execve("/bin/pingr", arr_err, envp);	// THIS WON'T WORK
		if (err == -1)
		{
			printf("Couldn't find program to execute OR Error in Command (Wrong Command)\n");
			return (2);
		}
		printf("THIS SHOULDN'T PRINT ON THE TERMINAL; THE EXECVE SUCCEED & OVERWRITE IT.\n\n");
	}
	else
	{
		int wait_status;
		// Parent Process
		wait(&wait_status);	
		/*
			- Checking if the Child Process Terminated Successfully/Normally without Errors.
			- If the WIFEXITED (WAIT IF EXITED) ;
				- if its return (!= 0) (which is true) -->> Normal Termination 
		*/
		if (WIFEXITED(wait_status))	// This is a MACRO that takes the returned wait_status variable to check its number
		{
			// This MACRO will return the status code (which is the return value that it exited with)
			int status_code = WEXITSTATUS(wait_status);
			if (status_code == 0)
				printf("\n\nSucceeded with status code %d\n\n", status_code);
			else
				printf("\n\nFailed with status code %d\n\n", status_code);
				// We get this error from above child our returns in case of this error
		}
		printf("\nSomething After execve (Post Processing is happening).\t\t<<<<<<<<--------------------\n\n");
	}

	return (0);
}
