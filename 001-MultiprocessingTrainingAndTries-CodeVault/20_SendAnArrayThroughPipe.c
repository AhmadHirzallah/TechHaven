#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>  // Added header for getpid/getppid/wait()

int	main (int argc, char **argv)
{
	(void) argc;
	(void) argv;

	int p_fd[2];
	if (pipe(p_fd) < 0)
		return (1);
	int pid = fork();
	if (pid < 0)
		return 2;
	if (pid == 0) // child process
	{
		printf("\n\nChild process.\n");
		close(p_fd[0]);
		int n; 
		int arr[10];
		srand(time(NULL));
		n = rand() % 10 + 1;	// generate from 1 to 10
		printf("Generated random n = %d\n", n);
		if (write(p_fd[1], &n, sizeof(int)) < 0)
			return (4);
		printf("write to the child n = %d\n", n);
		printf("Generated random numbers:  ");
		for(int i = 0; i < n; i++)
		{
			arr[i] = rand() % 11;
			printf("%d  ", arr[i]);
		}
		printf("\n");
		if (write(p_fd[1], arr, n * sizeof(int)) < 0)
			return (3);
		close(p_fd[1]);
		printf("Sent the array to the Parent through the pipe\n");
	}
	else	// Parent Process
	{
		close(p_fd[1]);
		int n;
		int arr[10];
		if (read(p_fd[0], &n, sizeof(int)) < 0)
		return (5);
		printf("\n\nParent process.\n");
		printf("Received n = (%d)\n", n);
		
		if (read(p_fd[0], arr, sizeof(int) * n) < 0)
			return (6);
		printf("Received array of integers\n");
		int sum = 0;
		for(int i = 0 ; i < n ; i ++)
			sum += arr[i];
		printf("Calculated Result of summation = %d\n\n", sum);
		close(p_fd[0]);
		wait(NULL);		// wait for the child for preventing zombies
	}

	return (0);
}