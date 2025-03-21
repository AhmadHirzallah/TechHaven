#include <stdlib.h>
#include <X11/keysym.h>
#include "mlx.h"
#include <stdio.h>

# define WIDTH 600
# define HEIGHT 800

/*
 * MLX_STRUCT
 * I stock all the data into a struct
 * because the handler function takes 
 * (void *)pointer_to_data
 * I need therefore this gimmick to 
 * pass more elements in one-go
*/
struct mlx
{
	void	*display_conn;
	void	*window;
	// void	*
};


typedef struct s_data
{
	struct mlx		mlx;
}                   t_data;

/*
 * HANDLER FUNCTION 
 * Every time a (key) is pressed this function is called
 *
 * - KEYSYM vs KEYCODE
 * 		- A keycode is a hardware-specific code sent by the keyboard for a key press, 
 * 		- while a keysym is its abstract representation, 
 * 			often used in software to identify the key regardless of hardware.
 * 🚨 MinilibX mac uses keycodes 🚨
*/
int handle_input(int keycode, t_data *data)
{
	printf("The key (%d) is has been pressed\n\n", keycode);
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(data->mlx.display_conn, data->mlx.window);
		mlx_destroy_display(data->mlx.display_conn);
		free(data->mlx.display_conn);
		exit (0);
	}
	return (0);
}

int main()
{
	t_data	data;


	data.mlx.display_conn = mlx_init();
	if (data.mlx.display_conn == NULL)
		return 1;
	
	/*
	 * WINDOW 
	 * Just another big boy malloc'd like: mlx_init();
	 *	
	 *	https://github.com/42Paris/minilibx-linux/blob/7dc53a411a7d4ae286c60c6229bd1e395b0efb82/mlx_new_window.c#L22
	*/
	data.mlx.window = mlx_new_window(data.mlx.display_conn, WIDTH, HEIGHT ,"My 2'nd MLX Window");
	if (data.mlx.window == NULL)
	{
		mlx_destroy_display(data.mlx.display_conn);
		free(data.mlx.window);
		return (2);
	}


	//	- We can have more than 1 window; below is the 2'nd window.
	// void *new_window = mlx_new_window(data.mlx.display_conn, WIDTH, HEIGHT ,"Window Number 2");
	// if (new_window == NULL)
	// {
	// 	mlx_destroy_display(data.mlx.display_conn);
	// 	free(data.mlx.window);
	// 	return (2);
	// }






    /*
     * HOOKS
     *  "Hooking into events" (react to events)
     * When I press a key, handle_input() is triggered
     * 💡 Every event is linked to its own prototype handler 💡
    */
	mlx_key_hook(data.mlx.window, handle_input, &data);


	// EVENT LOOP
	// Without this loop the process will stop immediately & now window will appear
	/*
	 * The minilibx library has a function called mlx_loop. 
	 * This function starts what's known as an event loop. 
	 * An event loop keeps the application running and constantly AND ;
	 * checks for events, such as user input (like mouse clicks or keyboard presses). 
	 * As long as the application is running, this loop continues to execute.

	IMPLEMENTATION
	https://github.com/42Paris/minilibx-linux/blob/7dc53a411a7d4ae286c60c6229bd1e395b0efb82/mlx_loop.c#L37

	The concept can be likened to:

		while (application is running) 
		{
			check for events;
				execute associated functions for those events;
		}
	*/
	mlx_loop(data.mlx.display_conn);



	/*
	 * 🚨 CLEAN UP is never reached due to the loop 🚨
	 * 		If i press control-C i will get LEAKS
	 *
	 * 		💡 I need EVENTs handling for that...💡
	*/
	mlx_destroy_window(data.mlx.display_conn, data.mlx.window);
	mlx_destroy_display(data.mlx.display_conn);
	free(data.mlx.display_conn);
	return (0);
}