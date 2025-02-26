#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
/*
	pipes are like something called fifos
	- fifo is a file type in which you can read or write from any process you opened
	- fifo is really an unnamed pipe.
	- We included <sys/stat.h> and <sys/types.h> and <errno.h>
*/
int main (int argc, char **argv)
{
	(void) argc;
	(void) argv;

	// To create a fifo file we use: We enter path and who can access the file
	//  this file is going to be able to be read from or wrote to by anybody using the system
	// We have to include <fcntl.h>	for performing (open)
	printf("Executing mkfifo\n\n");
	char *file_name = "my_fifo_file1";
	printf("creating %s\n\n", file_name);
	if (mkfifo(file_name, 0777) == -1)	// We can go terminal and type : (mkfifo any_name) but we do it in the program in this line
	{
		if (errno != EEXIST)
		{
			printf("Failed to create a fifo\n");
			return (-1);
		}
	}
	printf("%s is created\n\n", file_name);
	// Open (open()) returns the file descriptor (fd) of the file.
	printf("Openning the fifo %s created file\n\n", file_name);	// The system will stop at this and open() fails
	int fd = open(file_name, O_WRONLY);	// This problem (O_WRONLY); we only write; we want to read from the other pipe !
	// int fd = open(file_name, O_RDWR); // So we can fix this with this. so both fd (0 read) and fd (1 write) is opened so the data flow and every thing flow perfectly
	if (fd == -1)
	{
		printf("Error in openning the file.\n\n");
		return (-3);
	}
	// open failed because in unix system how it works.
	// openning the read or write (end) of fifo is blocked until the other end is also openned
	printf("fifo %s file is opened\n\n", file_name);
	int x = 79;
	printf("Trying to write into the %s file \n\n", file_name);
	if (write(fd, &x , sizeof(x)) == -1)
	{
		printf("Error in writting on file.\n\n");
		return (-2);
	}
	printf("wrote into the %s file Successfully.\n\n", file_name);
	close(fd);
	



	return (0);
}