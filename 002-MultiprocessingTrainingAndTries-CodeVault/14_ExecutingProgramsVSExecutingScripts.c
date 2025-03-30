#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>		// This is for the (Files Control) (open, close, ... etc).

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
	{
		// Child Process

		int fd = open("pingResults_14.txt", O_WRONLY | O_CREAT,  0777); 
		if (fd == -1)
		{
			printf("\n\nFile isn't opened for WRITING or not CREATED.\n\n");
			return (2);
		}

		// this (new_dup2_fd = 1) OR (new_dup2_fd = STDOUT_FILENO)
		printf("The fd to pingResults.txt: (%i)\n\n", fd); // on terminal
		int new_dup2_fd = dup2(fd, STDOUT_FILENO);
		printf("The Duplicated fd: (%i)\n\n", new_dup2_fd); // on the txt file after dup2
		// Because we don't want it; we have it exist in STANDARD OUTPUT:STDOUT_FILENO: (fd 1) by dup2.
		close(fd);
		/*
			- There is miss understanding of exec functions behaviours !
			- We execute the `executable OR binary` program (IN CHILD PROCESS).
			- With (*arr[] and its execve(...) everything works correctly).
			- But in case of piping like if we want to (grep) something from the output of the binary.
				- grep in linux let you filter the output of a program/binary
				- ping -c 1 google.com | grep "rtt"
					- output only the linex containing (rtt) keyword in it!
			- Will fails with *arr2[] as and output :
				- ' ping: "rtt": Name or service not known 
					Failed with status code 2				'
		*/

		// char *arr[]  = {"ping", "-c", "3", "Google.com", NULL};
		// int err = execve("/bin/ping", arr, envp);
		/*
			- Problem Description: 
				- Thinking the exec functions execute bash script (linux) or command  line scripts (windows)
				- This is False. 
					- In fact what it does it actually executes an exe/binary
					- Not a command line of sorts of something that can be parsed
				- when you exec(ping) it work as searching the binary/exe
					- as (whereis ping) in terminal but it don't use terminal; 
					- after finding the path of exe/binary; 
						- IMMIDIETLY IT IS EXECUTED WITHOUT GOING INTO THE BASH INTERPRETER.
				- SO exec(...) will execute the exe/binary immidietly without going to terminal or bash
					- C language directly talks with this executable/binary
				- The instruction: ping -c 1 google.com | grep "rtt" 
					- This is executed in terminal BY BASH TERMINAL;
						- The bash is responsible for executing the Binary.
					- The pipe "Command1 | Command2"
					-The pipe operator -> "|" is specific to the Bash.
				- In conlusion ; we send the exec functions
					1. Executable/Binary
					2. arguments of this executable/binary
						- Arguments will be parsed as (argv) by the exe and sent to it!
				- C Program exec Function ---Directly-->>> ping program
					- ping program then will raise a problem saying what is "|", grep, rtt???
						- which are (grep) is another exe/binary and rtt a argument of the grep and | is bash thing.  
		*/
		char *arr2[]  = {"ping", "-c", "3", "Google.com",
							"|", "grep", "\"rtt\"", NULL};
		int err = execve("/bin/ping", arr2, envp);
		if (err == -1)
		{
			printf("Couldn't find program to execute OR Error in Command (Wrong Command)\n");
			return (3);
		}
		printf("THIS SHOULDN'T PRINT ON THE TERMINAL IF THE EXECVE SUCCEED & OVERWRITE IT.\n\n");
	}
	else
	{
		// Parent Process
		int wait_status;
		wait(&wait_status);	
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