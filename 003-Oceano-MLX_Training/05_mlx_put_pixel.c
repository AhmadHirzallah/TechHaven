#include "mlx.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>

#define MALLOC_ERROR	1
#define	SIDE_LEN		800

typedef	unsigned char	byte;

/*
 * bitwise operation to get the color value..
 *
 * TLDR
 * i prefer #defines ...or better, writing directly in hexadecimal
*/
int	encode_rgb(byte red, byte green, byte blue)
{
    return (red << 16 | green << 8 | blue);
}


typedef struct	s_var
{
	void	*mlx;
	void	*win;
}				t_var;


void	color_screen(t_var *data, int color)
{
	for (int y = 0; y < SIDE_LEN; ++y)	
	{
		for (int x = 0; x < SIDE_LEN; ++x)
		{
			/*
			 * This function really suck 👎🏻
			 * 	~No buffer, i can literally see the pixels being drawn
			*/
			mlx_pixel_put(data->mlx,
						data->win, 
						x, 
						y, 
						color);
		}
	}
}

/*
 * KeySym values in X11/keysym.h
 * - https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h
 * - Try in command line
 *      - xev | grep --line-buffered -A 2 "KeyPress" 
*/
int	f(int keysym, t_var *data)
{
    printf("Key Event Triggered! Keycode: %d\n", keysym);

	if (keysym == 1506)
	{
		color_screen(data, encode_rgb(255, 0, 0));	
	}
	else if (keysym == 1508)
	{
		color_screen(data, encode_rgb(0, 0xff, 0));	
	}
	else if (keysym == 16842491)
	{
		color_screen(data, encode_rgb(0, 0, 0xff));	
	}	
	return 0;
}


// Didn't worked
// int f(int keysym, void *data)
// {
//     (void) data;
//     printf("Key Pressed! Keycode: %d, KeySym: 0x%X\n", keysym, keysym);

//     if (keysym == XK_r)
//         printf("R Key Pressed!\n");
//     else if (keysym == XK_g)
//         printf("G Key Pressed!\n");
//     else if (keysym == XK_b)
//         printf("B Key Pressed!\n");

//     return 0;
// }

// Didn't worked also
// int f(int keycode, void *param)
// {
//     (void) param;
//     if (keycode == 0x72) // XK_r
//         printf("R Key Pressed!\n");
//     else if (keycode == 0x67) // XK_g
//         printf("G Key Pressed!\n");
//     else if (keycode == 0x62) // XK_b
//         printf("B Key Pressed!\n");
//     return (0);
// }







/*
 * All the checks for errors like 
 * 		
 * 	~if (vars.mlx == NULL) exit(1);
 *
 * are not written to not clog te code!
 * But u know this stuff is a necessary evil 😂
*/
int	main()
{
	t_var	data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx,
								SIDE_LEN,
								SIDE_LEN,
								"My window");

	mlx_key_hook(data.win, f, &data);


	mlx_loop(data.mlx);
}
