#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// for using strlen and string functions
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>  // Added header for getpid/getppid/wait()


/*
Project Idea:
	- We need to work with 3 processes in total (2 child of same parent)
	- We need to pass an int around all the processes !.
	- Parent process send and variable (x) to the 1'st Child
		- 1'st Child do a summation to this (int x) for example (+ 5) summation
	- 1'st child will pass the new int (old + 5) to the 2'nd child
		- 2'nd Child receive the integer (old + 5) and perform 5 summation
		- new int x = old + 5 + 5
	- 2'nd Process then send the last (updated number : old + 5 + 5) to the main/parent process ! 
*/

/*
 Code Planning:
	- We will have Parent/Main process which only will create pipes and processes
	- We need 3 pipes;
		- Because pipes are unidirectional and the input of parent could go to 3rd child
			 before 2nd child and the process organization will be corrupted
		- So 3 pipes [3]; each have 2 fds [2] (for read[0] and write[1])
			- so in total we will have 6 FDS !!!!
			- All these 6 fds will be inherited in all childs !
			- Parent/Main have 6 FDS ;; 1'st Child have 6 FDS ;; 2'nd Child have 6 FDS.
			- So IN TOTAL WE WILL HAVE 18 FDS OPEN IN OUR SYSTEM
			- SO WE HAVE DO close (18) times !! in the whole C Code
			- This is the most important part when dealing with multiple pipes is with this 
				inheritance of file descriptors and enclosing all of them up because you
				don't want to let those file descriptors be opened as it will do a 
				program/executable problem as well as System Problem (waiting input as grep 
				command not stopped bec. p_fd[0] of main process forgot to be closed)

	- fork 1'st child process
	- fork 2'nd child process 

*/
int	main (int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;

	// All the file descriptors opened in a process when fork they will get duplicated into the other processes. 
	int p_fd[3][2];		// Because we will have 3 processes & data flow is between them.
	for (int i = 0 ; i < 3 ; i++)
	{
		// - This should handled in case of error in different way;
		//		- Because if pipe of FD 1 failed we have to close all previous FDS p_fd[1][0] p_fd[1][1]
		//			- But this need a lot of code so skip :)
		if (pipe(p_fd[i]) < 0)
			return (i + 1);	// error return 1 to 3
	}

	int p_id1 = fork();
	if (p_id1 < 0)
		return (4);
	/*
		- Deciding Writing and Reading pipes for each process;
			- Parent :
				- Read End  : p_fd[2][0]	(Receive from 2'nd Child Write End Pipe p_fd[2][1])
				- Write End : p_fd[0][1]	(Write to its pipe (p_fd[0] 1'st pipe) to send data to 1'st Child)
			- 1'st Child: 
				- Read End  : p_fd[0][0]	(Receive From Parent/Main Process  (Above) Write End).
				- Write End : p_fd[1][1]	Write next pipe; to send data to 2'nd Child Process
			- 2'nd Child:
				- Read End  : p_fd[1][0]	(Receive From 1'st Child (Above) Write End).
				- Write End : p_fd[2][1]	(Write next pipe) to send it to the Parent/Main Process

	*/
	if (p_id1 == 0) // 1'st Child ;; Only [0][0] and [1][1] is needed
	{
		close(p_fd[0][1]);
		close(p_fd[1][0]);
		close(p_fd[2][0]);
		close(p_fd[2][1]);
		int x;
		if (read(p_fd[0][0], &x, sizeof(int)) < 0)
			return (5);		// Have to close all opened fds before !
		printf("Received %d from Parent Process in 1'st Child.\n", x);
		x += 5;
		printf("Updated x value: x = (%d)\n", x);
		if (write(p_fd[1][1], &x, sizeof(int)) < 0)
			return (6);		// Close all opened FDS :)
		printf("Write (x : [%d]) to the next process by pipe\n\n", x);
		close(p_fd[0][0]);
		close(p_fd[1][1]);
		return (0);			// No more need for the Child !
	}	
	// - We have closed (6 FDS of pipes on one process);
	//	 	- this is what should be done when having many pipes; as pipes create fds which should be all closed
	int p_id2 = fork();
	if (p_id1 < 0)
		return (7);
	// 2'nd Child Process ;; p_fd[1][0]	p_fd[2][1]	are only the needed FDS.
	if (p_id2 == 0)	
	{
		close(p_fd[0][0]);
		close(p_fd[0][1]);
		close(p_fd[1][1]);
		close(p_fd[2][0]);
		int x;
		if (read(p_fd[1][0], &x, sizeof(int)) < 0)
			return (8);		// Have to close all opened fds before !
		printf("Received %x from 1'st Process in 2'nd Child.\n", x);
		x += 5;
		printf("Updated x value: x = (%d)\n", x);
		if (write(p_fd[2][1], &x, sizeof(int)) < 0)
			return (9);		// Close all opened FDS :)
		printf("Write (x : [%d]) to the next process by pipe\n\n", x);
		close(p_fd[1][0]);
		close(p_fd[2][1]);
		return (0);			// No more need for the Child !
	}
	// Parent Process.	
	//	Only need this FDS: p_fd[2][0]	p_fd[0][1]	
	close(p_fd[0][0]);
	close(p_fd[1][0]);
	close(p_fd[1][1]);
	close(p_fd[2][1]);
	int x;
	printf("Please enter the intial number:  ");
	scanf("%d", &x);
	if (write(p_fd[0][1], &x, sizeof(int)) < 0)
		return (10);
	printf("\n\nWrite (x : [%d]) to the next process\n\n", x);
	if (read(p_fd[2][0], &x, sizeof(int)) < 0)
		return (11);		// Have to close all opened fds before !
	printf("Received %d in Parent Process.\n", x);
	printf("\nFinal Result = [%d]\n:)\n", x);
	close(p_fd[0][1]);
	close(p_fd[2][0]);
	waitpid(p_id1, NULL, 0);
	waitpid(p_id2, NULL, 0);
	return (0);
}