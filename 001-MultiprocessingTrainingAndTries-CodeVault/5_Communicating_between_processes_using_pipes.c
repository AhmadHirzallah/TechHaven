#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>	// used for pipe and fork
#include <sys/wait.h>

int main(int argc , char **argv)
{
	(void) argc;
	(void) argv;
	/*
		- How to communicate between processes without just copying things over (using fork())
		- After forking; we want to send/receive things from/between processes
		- There is a functionallity in c called pipe ! (Which means a in memory file) : file having sort of buffer/memory ; and you can write and read from it
		
		- Takes array of 2 integers ; which are the file descriptors for the (pipe())
		- fd is like a key to access a file that is where we want read or write data.
	*/
	int fd[2];
	/*
		- when we send fd as parameter of pipe ; then this is going to save inside this array the file descriptors (fds) that is opens when we create the pipe
		- So fd have the fds of the pipe so we can read or write to it.
		- when we do (fopen()) we will have only 1 file descriptor but in this case we got multiple
		- pipe returns 0 in successful ; 
		- return -1 when it fails
	*/
	short result = pipe(fd);
	if (result == -1)
	{
		printf("An error occured with opening the pipe\n");
		return (1);
	}
	/*
		- When we fork ; the file descriptors (fd[2]) will be coppied over ! and these fds not only coppying integers !! 
			- Behind the scence; those file descriptors are also assigned to the new newly created process so they get inherited
				- That mean well that means that if you for example if you close the fd at a point in a one process ;
					- that (same file descriptor) in the other process (remains) (open) so they sort of independed (fds) from each other.argc
	*/
	int p_id = fork();
	if (p_id == -1)
	{
		printf("Error in forking.\n\n");
		return (2);
	}
	/*
		* What we want to do:
			- Asks the user to input a number and then it sends it to the other process 
				- Send it to the parent process from the child process.
					- Then The Parent will print it on the screen or do any needed operations on it
	*/

	/*
		fd[0] : read
		fd[1] : write
	*/
	if (p_id == 0)
	{
		close(fd[0]); 	// Because in child we need to write(use fd[1]) not to read using fd[0]
		// We will input x from the (Child Process)inorder to send it to the (Parent Process):
		int x;
		printf("Input a number:  ");
		scanf("%d", &x);
		// write is used to output into (Any File/Any Pipe) just by specifying the (Target (fd))
		if (write(fd[1] , &x, sizeof(int)) == -1)
		{
			printf("Error in writing.\n\n");
			return (3);
		}
		close(fd[1]);
	}
	else  // We are in Parent
	{
		close(fd[1]); // We want to read (take data from child); not to write or send (which is fd[1])
		int x;
		if (read(fd[0], &x, sizeof(int)) == -1)
		{
			printf("Error in Reading.\n\n");
			return (4);
		}
		close(fd[0]);	// close fd[0] after reading using it.
		printf("Received Number (in Parent Process) is:  %d\n\n", x);
	}
	return (0);
}