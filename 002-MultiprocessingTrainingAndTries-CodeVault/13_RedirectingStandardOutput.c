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
	/*
		- Our purpose is to tell the ping to not print on the terminal (standard output)
		- In case that we want to print/output all the data on file rather than terminal 
		-  
	*/
	if (pid == 0)
	{
		// Child Process
		
		/*
			- Create file if not exist; we open it for WRITING ONLY, 0777 is permissions (set full permissons)
			- File Descriptors (fds) are just a numbers that are unique across the process (one process itself)
			- So 2 processes can have the same file descriptors with number (3 for example)
				- But same process can't have 2 FDs with the same number; every FD is 1 unique.
			- FDs represent a (KEY or HANDLE) to an input or output resources
				- Could be a file; terminal input, terminal output, standard output/input/error_output , or pipes
					- So they are just a keys/handles that you can read or write from/to it.
			- When ever you start a process; Linux will opens certain FDs for you; For Example:
				- 	(0)		:		(STDIN)		: [[[	read(0) = scanf("...")	]]]
				- 	(1)		:		(STDOUT)	: [[[	write(1, ....)	]]]
				- 	(2)		: (STDERR) : [[[ Where all the errors go to; Similar to STDOUT; but it show in red]]]
				-	(3)		:		Any File you opens as (pingResults.txt). 
			- All these FDs; are opened by default before you even get to the first line in main(...) .
		*/
		int fd = open("pingResults.txt", O_WRONLY | O_CREAT,  0777); 
		if (fd == -1)
		{
			printf("\n\nFile isn't opened for WRITING or not CREATED.\n\n");
			return (2);
		}
		/*
			- If we want to what ever `ping` output to the terminal
				 to be output to a file like (pingResults.txt)
				- We want to replace the (1 FD : STDOUT) --->>> to point into (pingResults.txt).
			- This can be achieve using `dup()` function in Linux.
			- `dup(fd)` : `dup` takes a parameter which is:
				- just a single file descriptor FD;
				- So it will return another (New) FD for our (pingResults.txt)
			- So for example: 
				-	(3)	 	:		opened above for (pingResults.txt)
				-	(4)	 	:		dup(fd (3 of pingResults.txt))
					- So this will open (for example (FD = 4)) pointing to FD=3 of pingResults.txt
		*/
		int new_dup_fd = dup(fd);
		(void) new_dup_fd;
		/*
			- But this wan't we want; we want to make the STDOUT go into our file
				- Overwrite the STDOUT and remove it; then replace it with FD=3 or FD=4 that we opened!!
			
			- This Replacement/Overwritting of STDOUT can be done by dup2()
			
			- dup2(FD, 1) OR dup2(FD, STDOUT);
				- 1'st Param. : The FD that we want to (clone/duplicate)
				- 2'nd Param. : FD2 that will be replaced;
					- is the value that  we want the FD1 (1'st parameter) to replace it
				- This wont create/open a new FD ! it will only overwrite the specified STDOUT
					- To make it point into the FD !
				
				- What will happen that (2'nd Param STD2) FD2 will be close() (Closed stream).
				- Open the 2'nd Param (FD2) again after closing but 
					for the newFD (1'st Param.) as fd=3 (opened file pingResults.txt) 
			
			- dup2 :::		 Duplicate FD to FD2, closing FD2
		*/
		// this (new_dup2_fd = 1) or (new_dup2_fd = stdout)
		printf("The fd to pingResults.txt: (%i)\n\n", fd); // on terminal
		int new_dup2_fd = dup2(fd, STDOUT_FILENO);
		printf("The Duplicated fd: (%i)\n\n", new_dup2_fd); // on the txt file after dup2
		// Because we don't want it; we have it exist in STANDARD OUTPUT:STDOUT_FILENO:(fd 1) by dup2.
		close(fd);
		char *arr[]  = {"ping", "-c", "3", "Google.com", NULL};
		/*
			- This hello will be output into the (pingResults.txt);
			- because we do overwrite the stdout to point to fd (the opened (txt) file)
		*/
		printf("Hello");
		/*
			- The exec will overwrite/replace (the code/the memory)
				- but it doesn't change the process ID
				- it won't change the file descriptors that are already opened so those remain.
			- ping program always print on STDOUT_FILENO (STANDARD OUTPUT) (TERMINAL)
				- But it will be printing to the dup2 `.txt` file the overwrite it.
		*/
		int err = execve("/bin/ping", arr, envp);
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