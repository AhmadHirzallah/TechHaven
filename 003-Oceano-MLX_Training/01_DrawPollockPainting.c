#include "mlx.h"
#include "stdio.h"

int main()
{
	/*
		- This is starting the connection with graphical server & it gives back a pointer to the connection
		- This how we estableshed a connection with the graphical server.

	*/
	void *mlx_connection =  mlx_init();
	(void) mlx_connection;

	return (0);
}
