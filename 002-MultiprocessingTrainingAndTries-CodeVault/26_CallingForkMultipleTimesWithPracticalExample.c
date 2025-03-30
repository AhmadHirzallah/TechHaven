#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// for using strlen and string functions
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>  // Added header for getpid/getppid/wait()


#define CHILD_PROCESSES_NBR 10

/*
	- Idea is to call fork multiple times so we can create any
		 number of processes as we want.
	- Main/Parent Process is having a int number (read from user)
	- Main Process passes this number to a child process
	- Child process Receive the nbr and Increament it by 1
	- Then it send it to next child; and next child do the same
	- At end we repass it to the Parent/Main Process and print it
*/

/*
	Implementation:
	- For 2 processes program we need  1 pipe
	- For 3 Processes we need 3 pipes
	- For 4 Processes we need 4 pipes
	- Lets consider case of 4 processes.
		1. (1) process is main 
			- we need to create 3 Child Processes by fork
		2. We need to create 4 pipes (nbr of childs (3) + parent (1)) 
			- this is equal to (nbr of forks + 1)
*/
int	main (int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	
	int	p_ids[CHILD_PROCESSES_NBR];
	int pipes_fds[CHILD_PROCESSES_NBR + 1][2];				
	for (int i = 0 ; i < (CHILD_PROCESSES_NBR + 1) ; i++) // We created the pipes and handled them
	{
		if (pipe(pipes_fds[i]) == -1)
			return (1);
	}

	// Create a number of processes
	for (int i = 0 ; i < CHILD_PROCESSES_NBR; i++)
	{
		p_ids[i] = fork();
		if (p_ids[i] == -1)
			return (2);
		if (p_ids[i] == 0)	// Current Child Process after forking
		{
			/*
				- We need a standard of which process uses which pipe 
				- Each (CHILD) have a process id [p_id[i]] that we can use
				- 1'st Child p_ids[0] == 0 (Of the 1'st fork())
					- 1'st child (which its index i = 0)	have:
						- Reading:	1'st pipe index 0 : pipe_fds[i = 0][0] bec. Parent pipe_fds[i = 0][1] write to it.
						- Writing: 	2'nd pipe : pipe_fds[(i + 1) = (1)][1]
					- 2'nd child (which its index = 1)	have:
						- Reading: 2nd pipe index of 1 : pipe_fds[i = 1][0]
						- Writing: 3rd pipe index of 2 : pipe_fds[i+1 = 2][1] 
					
					
				^^^ Any Child : reading --->  pipe_fds[i][0]	;;;; Writing ---> pipe_fds[i + 1][1]
				- But we have Different cases for Parent and Last Child Processes:
					- Parent -> 
						-Writing pipe_fds[0][1]		;;;;;
						- Reading pipe_fds[LAST_PROCESS_ID(3 : 4TH PROCESS)][0]
				
				- Note &&&& : Each process all the other pipes that we have created (don't use before & used after)
					- 4 pipes created ; all are forked/clone to all the processes !!
						- 4 * 2 = 8 FDS in each process => (8 * 4 = 32 FDS are opened and all should be closed).
			*/
			for (int k = 0 ; k < CHILD_PROCESSES_NBR + 1 ; k++)
			{
				if (i != k)
					close(pipes_fds[k][0]);
				if ((i + 1) != k)
					close(pipes_fds[k][1]);
			}
			int x;
			
			if (read(pipes_fds[i][0], &x, sizeof(int)) < 0)
				return (3);
			printf("\nRead a nbr = (%d)\n", x);
			x++;
			printf("Performed Summation => nbr = (%d)\n", x);
			if (write(pipes_fds[i + 1][1], &x, sizeof(int)) < 0)
				return (4);
			printf("Writted a number => nbr = (%d)\n", x);

			close(pipes_fds[i][0]);
			close(pipes_fds[i + 1][1]);

			// - Because we are terminating each Child after finishing processing after forking 
			// 		- So we don't have fork 2^n (no forking of parents and childs) only Main/Parent is forking
			return (0);		// Or we can break; of loop so no more fork() is performed on any child; only parent will do
			
		}
		// wait(NULL);	// This is wrong to do ! you will wait every process to finish before forking a new one (make it sequentaly)
						// So we don't have multiprocesses work togother; we don't take advantage of multiprocessing if only 1 or 2 are executing.
						// We have to do it in a separated for loop (not in same of fork() loop)
	}

	// Main process; All the Childs are Terminated by return 0 in its above loop.
	int x;
	printf("Please enter a number:   ");
	scanf("%d", &x);
	
	for (int k = 0 ; k < CHILD_PROCESSES_NBR + 1 ; k++)
	{
		if (CHILD_PROCESSES_NBR != k)
			close(pipes_fds[k][0]);
		if (0 != k)
			close(pipes_fds[k][1]);
	}
	if (write(pipes_fds[0][1], &x, sizeof(int)) < 0)
		return (5);
	printf("Writted a number => nbr = (%d)\n", x);

	if (read(pipes_fds[CHILD_PROCESSES_NBR][0], &x, sizeof(int)) < 0) // CHILD_PR... IS Last Index (Last available Pipe)
		return (6);
	printf("\nRead a nbr = (%d)\n", x);

	printf("\n\nLast Result = (%d)\n\n", x);

	close(pipes_fds[0][1]);
	close(pipes_fds[CHILD_PROCESSES_NBR][0]);

	for (int i = 0 ; i < CHILD_PROCESSES_NBR; i++)
		wait(NULL);	//	so that way we wait for all the child processes to finish execution properly.

	return (0);
}
