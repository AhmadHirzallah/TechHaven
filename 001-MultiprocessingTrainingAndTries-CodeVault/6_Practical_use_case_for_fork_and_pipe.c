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
	We want to sum the elements in a manner that takes advantages of multiple processors in computer !
	The approach sums all nbrs up by dividing the array into two;
	 and leaving half of the array to be calculated by one of the process;
	 and the other one by the other process;
	 and at the end both processes will have a partial sum and one process
	 will write that partial sum to the pipe and the other one is going to read it
	 and then it sum them togother.
	*/
	int arr[] = {1, 2 , 3 , 5  ,10  , 30 , 50, 50};
 	// Because sizeof(arr) will give the number of bytes in the array
	int array_size = sizeof(arr) / sizeof(int);
	int fd[2];
	int start_index;
	int end_index;
	if (pipe(fd) == -1)
	{
		printf("Error in pipe\n\n");
		return (1);
	}
	int p_id = fork();
	if (p_id == -1)
	{
		printf("Error in forking\n\n");
		return (2);
	}
	if (p_id == 0) 	// Child process child from 0 until middle.
	{
		start_index = 0;
		end_index = start_index + (array_size / 2);
	}
	else	// Parent process start from middle until end.
	{
		start_index = array_size / 2;
		end_index = array_size;
	}
	int sum = 0;
	int i = start_index;
	while (i < end_index)
	{
		sum += arr[i];
		i++;
	}
	// Prining is in parrallel not at same time :) ; child could be before parent or vice versa.
	printf("Calculated Partial sum: (%d)\n", sum);

	if (p_id == 0)	// in child ; send the data to the parent
	{
		close(fd[0]);
		if (write(fd[1], &sum , sizeof(sum)) == -1)
		{
			printf("Failed in writting.\n\n");
			return (3);
		}
		close(fd[1]);
	}
	else	// In Parent ; we are receiving (reading) data from Child
	{
		int sum_of_child;
		close(fd[1]);
		if (read(fd[0], &sum_of_child, sizeof(sum_of_child)) == -1)	// or sizeof(int)
		{
			printf("Failed in reading.\n\n");
			return (4);
		}
		close(fd[0]);
		int total_sum = sum_of_child + sum;
		printf("\nThe Total Sum is (%d)\n", total_sum);
		wait(NULL);
	}

	return (0);
}