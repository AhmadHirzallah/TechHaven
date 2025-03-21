#include "mlx.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>

#define MALLOC_ERROR    1
#define SIDE_LEN        800

/*
 * IMAGE DATA
 * 
 * Why line_len? 
 * The number of bytes per line may be larger than (SIDE_LEN * bytes_per_pixel)
 * because of alignment requirements. This is necessary for efficient memory access.
 *
 * ENDIAN:
 * Colors are stored in 32-bit values, but the byte order depends on the system’s endian.
 * We usually ignore this detail when using functions that work with full pixel values.
 */
typedef struct s_img
{
    void    *img_ptr;
    char    *img_pixels_ptr;
    int     bits_per_pixel;
    int     endian;
    int     line_len;
}               t_img;

/*
 * This struct contains all the mlx stuff and the image where the pixels are buffered.
 */
typedef struct s_var
{
    void    *mlx;
    void    *win;
    t_img   img;
}               t_var;

/*
 * ft_pixel_put: Plot a pixel in a 2D image buffer.
 *
 * Coordinates convention:
 *   - col: horizontal position (column)
 *   - row: vertical position (row)
 *
 * The offset is computed as:
 *   offset = (line_len * row) + (col * (bits_per_pixel / 8))
 * 
 *  - img->img_pixels_ptr is declared as a char*. In C, pointer arithmetic on a char* works in single-byte increments.
 *  - Adding offset (which is in bytes) to img->img_pixels_ptr gives you the memory address where the pixel's data starts.
 *  - Casting to unsigned int *:
 *      -  
 */
void ft_pixel_put(t_img *img, int col, int row, int color)
{
    int offset;

    offset = (img->line_len * row) + (col * (img->bits_per_pixel / 8));

    *((unsigned int *)(img->img_pixels_ptr + offset)) = color;
}

/*
 * ft_color_screen: Fill the entire screen with the specified color.
 * Replaced for loops with while loops per coding standard.
 */
void ft_color_screen(t_var *data, int color)
{
    int row;
    int col;

    row = 0;
    while (row < SIDE_LEN)
    {
        col = 0;
        while (col < SIDE_LEN)
        {
            ft_pixel_put(&data->img, col, row, color);
            col++;
        }
        row++;
    }
}

/*
 * ft_handle_key: Process key events to change the screen color.
 */
int ft_handle_key(int keysym, t_var *data)
{
	if (keysym == 1506) // Red
    {
        ft_color_screen(data, 0xff0000);
    }
	else if (keysym == 1508) // Green
    {
        ft_color_screen(data, 0xff00);
    }
	else if (keysym == 16842491) // Blue
    {
        ft_color_screen(data, 0xff);
    }
    else if (keysym == XK_Escape)
        exit(1);

    // Push the updated image to the window
    mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);

    return 0;
}

/*
 * main: Initialize MLX, create a window and an image, and set up the key hook.
 */
int main()
{
    t_var   vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, SIDE_LEN, SIDE_LEN, "My window");

    /* Create an image and retrieve its data pointer */
    vars.img.img_ptr = mlx_new_image(vars.mlx, SIDE_LEN, SIDE_LEN);
    vars.img.img_pixels_ptr = mlx_get_data_addr(vars.img.img_ptr,
                                                &vars.img.bits_per_pixel,
                                                &vars.img.line_len,
                                                &vars.img.endian);

    printf("Line_len %d <-> SIDE_LEN %d\n"
           "bpp %d\n"
           "endian %d\n", vars.img.line_len, SIDE_LEN, vars.img.bits_per_pixel, vars.img.endian);

    mlx_key_hook(vars.win, ft_handle_key, &vars);
    mlx_loop(vars.mlx);

    return 0;
}
