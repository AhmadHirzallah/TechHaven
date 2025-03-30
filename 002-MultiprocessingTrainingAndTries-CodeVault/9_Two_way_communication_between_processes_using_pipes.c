#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>

/*
	- We want to genarate a random number in Parent Process;
	- Then send it to the child process (Parent will Write) and (Child will Read)
	- Child will perform an operations; like *4 or any thing other than that.
	- Child will send (Write) the new data to the (Parent) and Parent will (Read) from the Child and print the final output
*/
int main (int argc, char **argv)
{
	(void) argc;
	(void) argv;

	int	pipe_chtopa[2];		//	Child -->>	Parent
	int pipe_patoch[2];		//	Parent -->>	Child
	if (pipe(pipe_patoch) == -1)
	{
		printf("Failed in creating a pipe.\n\n");
		return (-2);
	}
	if (pipe(pipe_chtopa) == -1)
	{
		printf("Failed in creating a pipe.\n\n");
		return (-3);
	}
	int p_id = fork();
	if (p_id == -1)
	{
		printf("Failed in forking.\n");
		return (-4);
	}
	if (p_id == 0)	//	Child Process.
	{
		close(pipe_chtopa[0]);
		close(pipe_patoch[1]);
		int x;
		printf("\n\nReading a number from parent:\n");
		if (read(pipe_patoch[0], &x, sizeof(int)) == -1)
		{
			printf("Error in reading.\n");
			return (-6);
		}
		printf("Read a number from parent successfully: (%d)\n", x);
		x *= 10;
		printf("Performed an operation on the number as (after): %d\n", x);
		printf("Sending the number (%d) to the Parent using (write); after operated on it\n", x);
		write(pipe_chtopa[1], &x , sizeof(x));
	}
	if (p_id != 0)	//	Parent Process.
	{
		close(pipe_chtopa[1]);
		close(pipe_patoch[0]);
		srand(time(NULL));
		int x = rand() % 3 + 1;
		printf("Generated a random number in parent: (%d)\n", x);
		printf("Sending the random number from parent to the child (%d)\n", x);
		if (write(pipe_patoch[1], &x, sizeof(int)) == -1)
		{
			printf("Error in writting.\n");
			return(-5);
		}
		if (read(pipe_chtopa[0], &x, sizeof(int)) == -1)
		{
			printf("Error in reading.\n");
			return (-6);
		}
		printf("Finally -- Received result is: (%d)\n", x);
		close(pipe_chtopa[0]);
		close(pipe_patoch[1]);
	}

	wait(NULL);
	return (0);
}
