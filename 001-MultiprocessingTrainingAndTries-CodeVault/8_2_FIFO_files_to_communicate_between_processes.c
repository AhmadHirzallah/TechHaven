#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

int main(int argc , char **argv)
{
	int arr[5];
	int fd;
	int i;
	int size;
	int sum;

	size = 5;
	fd = open("fifo_sum", O_RDONLY);
	if (fd == -1)
	{
		printf("Error in openning\n");
		return (-2);
	}
	if (read(fd, arr, (sizeof(int) * 5)) == -1)
	{
		printf("Error in reading\n");
		return (-3);
	}
	close(fd);
	i = 0;
	while (i < size)
		sum += arr[i++];
	printf("Result of summation is: (%d)\n", sum);
	return (0);
}
