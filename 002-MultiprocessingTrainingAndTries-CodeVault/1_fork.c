#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//We need unistd to use fork function
// Unistd is a linux specific library ; it is only found on linux -- some people do same for windows
#include <unistd.h>

/*
Every Single Process in Windows, Linux (everywhere) has a process ID;
So when you create a process it will always have a process ID
*/

int	main (int argc, char **argv)
{
	(void) argc;
	(void) argv;

	// int p_id = fork();
	// printf("hello world\n");
	// Some info Below :
	/*
		Now after forking; We will have 2 separated p_id (ID NBRS)
		the main process and the other one is going to be in the child process now
		- ID in the child process is always going to be 0; 
		- this fork function will (Clone) the calling process;;; Creating an exact copy.
		- Returns (-1) for errors --- Returns (0) to the (New:Child) processes :) 
		- If your ID is (0) then you are in the (Main) process ;; If your ID isn't you are in the (Parent-Main) Process
	*/
	// printf("Process ID is: %d\n", p_id);

	// int	p_id = fork();
	// if (p_id == 0)
	// 	printf("\nHello :) ;; From Child -- ID = (%d)\n\n ", p_id);
	// else
	// 	printf("\n\nHello :) ;; From Parent -- ID = (%d)\n", p_id);


/*
These processes both continue executing from that line (41) forward; then 2 processes will be forked in line (42) so (2 * 2 = 4)
*/
	// int p_id = fork();
	// int p_id2 = fork();
	// printf("Process ID is: %d\n\n", p_id);
	// printf("Process ID is: %d\n\n", p_id2);




	// fork();
	// fork();
	// fork();
	// fork();
	// printf("Hello\n");
	



	int id = fork();
	int	id2;
	/*	Which means that if i am a Parent/Main Process; Perform fork()	*/
	if (id != 0)
		id2 = fork();
	printf("Hello; I am (%d)\n", id2);
	/*
		Output Example:
						Hello; I am (-9736)
						Hello; I am (52629)
						Hello; I am (0)
	*/
	

	return (0);
}
