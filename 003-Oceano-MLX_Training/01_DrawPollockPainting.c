#include "mlx.h"
#include "stdio.h"
# include <stdlib.h> // for rand() function
# include  <time.h>

enum e_win_size
{
	WIDTH = 1920,
	HEIGHT = 800
};

/*
	- void *mlx_ptr;	Pointer to the MLX connection (returned by mlx_init())
	- void *win_ptr;	Pointer to the MLX window (created by mlx_new_window())
	- void *img_ptr;	Pointer to an image (if using mlx_new_image())
	- char *img_data;	Pointer to raw pixel data (if using mlx_get_data_addr())
	- int width;	Width of the window or image (if applicable)
	- int height;	Height of the window or image (if applicable)
	- int bpp;	Bits per pixel (for image data)
	- int endian;	Endian format (for image data)
	- int line_size;	Bytes per line (for image data)
*/
struct s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*img_data;
	int		color;
	int 	width;
	int		height;
	int		bpp;
	int		line_size;
};

struct s_iterators
{
	int x;
	int y;
	int temp;
};




int main()
{
	/*
		- This is starting the connection with graphical server & it gives back a pointer to the connection
		- This how we estableshed a connection with the graphical server.

	*/
	struct s_mlx_data	mlx;
	struct s_iterators	iters;

	
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "Ahmad 1'st Mlx Project ; Palloc Paint");

	// - Draw a diagonal line like this : (\)
	// iters.x = 0;
	// while (iters.x < 100)
	// {
	// 	mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, 250 + iters.x, 250 + iters.x , 0xFF00000);
	// 	iters.x++;
	// }
	

	// - Draw a Red Window:

	// iters.x = 0;
	// iters.y = 0;
	// while (iters.y < HEIGHT)
	// {
	// 	iters.x = 0;
	// 	while (iters.x < WIDTH)
	// 	{
	// 		mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, iters.x , iters.y , 0xFF0000 );
	// 		iters.x++;
	// 	}
	// 	iters.y++;
	// }
	



//	- Draw a red square:

	// iters.x = WIDTH * 0.1;
	// iters.y = HEIGHT * 0.1;
	// while (iters.y <  HEIGHT * 0.9)
	// {
	// 	iters.x = WIDTH * 0.1;
	// 	while (iters.x < WIDTH * 0.9)
	// 	{
	// 		mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, iters.x , iters.y , 0xFF0000 );
	// 		iters.x++;
	// 	}
	// 	iters.y++;
	// }



//	- Draw a palloc:
	iters.x = WIDTH * 0.1;
	iters.y = HEIGHT * 0.1;
	mlx.color = 0xFFFFFF;
	srand(time(NULL));
	while (iters.y <  HEIGHT * 0.9)
	{
		iters.x = WIDTH * 0.1;
		while (iters.x < WIDTH * 0.9)
		{
			mlx.color = rand() % 0x1000000;	// range from 0 -> 0xFFFFFF (less than 0x1000000 by one which is 0xFFFFFF)
			mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, iters.x , iters.y , mlx.color);
			iters.x++;
		}
		iters.y++;
	}
	mlx_string_put(
					mlx.mlx_ptr,
					mlx.win_ptr,
					WIDTH * 0.80,
					HEIGHT * 0.95 ,
					rand() % 0x1000000,
					"This is created by Ahmad; @Copy rights are reserved."
					); 

	mlx_loop(mlx.mlx_ptr);



	return (0);
}
