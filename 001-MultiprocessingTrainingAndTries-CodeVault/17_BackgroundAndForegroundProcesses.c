#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>	// usleep
#include <time.h>
#include <sys/wait.h>
#include <signal.h>	

/*
	- putting a process in the background and bringing it back to the foreground.
	- bringing a process to the background from forground really means actually stopping the process
	- if we launch the program from system (terminal or cmd) : 
		- ./program
		- and if we start the program; which ask the user for input;
			- then instead of typing in a number I say oh I have to go on my lunch break 
				so I'm going to actually stop this process
			- you can hit (ctrl + Z) on the keyboard to stop the program from execution and displaying
		
		- ./program -----> input a number:  ----> 	ctrl + z -----> [1]+  Stopped                 ./program
	- Process has stopped DOESN'T mean that process has terminated 
		- there's a big difference between the two (stop & termination).
		- (Termination) means that the program reached a an exit call or it reached
			 the return statement in main & its execution is done & all the memory
			 has been freed and were done but
		- (Stopping)  the process is more like Pausing the process
			- where it's like stuck at a certain line of code (which ever happens) to be 
				and it waits for a signal to (Continue as SIGCONT) its (Execution)

	- Continuing the program:
		- entering in system/terminal : ((fg)) command ----means--> (foreground)
			- will get the last process (pause process) to forground and Continue it 
			- fg = sending (SIGCONT) to the paused process using (ctrl+z) in background
				inorder to make it continue executing
	- Ctrl + z = SIGTSTP not SIGSTP ; they are quite same with no difference both 
		are stopping the process which can be Continued using SIGCONT
	- then we do (fg) in command line which is doing as SIGCONT
*/
int main(int argc, char **argv)
{
	system("clear");
	(void) argc;
	(void) argv;
	/*
		Good Info:
			- fork() will produce a child that its (pid == 0) 
			- but also in the parent process (which pid != 0) it will have child id in pid variable
				- If we do in Child Process (getpid) (get process id) then it will get the ID of child
				- Also this value of getpid of the child will have 100% the same value of pid of (pid = fork())
			- so the fork() will make clone of the parent ; but also return the (child getpid) 
			- the child inside the program will have (pid of fork) of value (0) 
				- but this 0 isn't its pid or id nbr; it is C language function does.
	*/

	int x ;
	printf(("input a number:  "));
	scanf("%d", &x);
	printf("Result (%d * 5) = (%d)\n", x, (x * 5));

	return (0);
}
