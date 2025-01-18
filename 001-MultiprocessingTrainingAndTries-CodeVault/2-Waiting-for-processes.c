#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/wait.h>


int main (int argc, char* argv[])
{
	int id = fork();
	int n;


	if (id == 0)		// Setting the Child Starting From 0;
		n = 1;
	else
		n = 6;		// Setting the (Main - Father) Starting From 6

	if (id != 0)		// This is the Parent it should wait for children !
		wait(NULL);

	int i;

	for (i = n; i < n + 5; i++)
	{
		printf("%d ", i);

		// Because printf uses buffer and output could take long time so we can do this to force printing from buffer before waiting
		fflush(stdout);
	}

	if (id != 0) printf("\n");	// Not Child :: Parent ---> Child first : 1 to 5 ; Parent Next : 6 to 10  ---> != 0 if Parent Print new line

	return (0);
}

