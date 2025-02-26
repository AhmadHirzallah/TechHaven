#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>		// This is for using of errno variable ; we check the it is (errno != ECHILD)

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	for (int i = 0; i < 10; i++)
		fork();
	
	int id1 = fork();
	int id2 = fork();
	if (id1 == 0)
		if (id2 == 0)
			printf("We are process (y)\n\n");
		else
			printf("We are process (x)\n\n");
	else
		if (id2 == 0)
			printf("We are process (z)\n\n");
		else
			printf("We are the (Parent) process.\n\n");
	while (wait(NULL) != -1 || errno != ECHILD)
			printf("Waited for a child to finish !!!\n\n");
	return (0);
}
