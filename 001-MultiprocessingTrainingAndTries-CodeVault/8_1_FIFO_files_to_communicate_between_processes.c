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

	srand(time(NULL));
	i = 0;
	size = 5;
	while (i++ < size)
	{
		arr[i] = rand() % 5 + 1;
		printf("Generated (%d)\n", arr[i]);
	}
	fd = open("fifo_sum", O_WRONLY);
	if (fd == -1)
	{
		printf("Error in openning\n");
		return (-2);
	}
	if (write(fd, arr, signed))

}