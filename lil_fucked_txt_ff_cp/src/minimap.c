/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:09:40 by wel-safa          #+#    #+#             */
/*   Updated: 2025/04/29 20:33:20 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Puts pixel on image at coordinates (x, y)
If bits per pixel is not 32, we call mlx_get_color_value to translate color
to fit the bits per pixel requirement of the image.
The bits position depends on the computer's endian,
bits are assigned accordingly.
*/
void	put_pixel_to_img(void *mlx, t_img *img, int x, int y, int color)
{
	int	pixel;

	if (img->bbp != 32)
	{
		color = mlx_get_color_value(mlx, color);
	}
	pixel = (y * img->line_length) + (x * 4);
	if (img->endian == 1)
	{
		img->addr[pixel + 0] = (color >> 24);
		img->addr[pixel + 1] = (color >> 16) & 0xFF;
		img->addr[pixel + 2] = (color >> 8) & 0xFF;
		img->addr[pixel + 3] = (color) & 0xFF;
	}
	else if (img->endian == 0)
	{
		img->addr[pixel + 0] = (color) & 0xFF;
		img->addr[pixel + 1] = (color >> 8) & 0xFF;
		img->addr[pixel + 2] = (color >> 16) & 0xFF;
		img->addr[pixel + 3] = (color >> 24);
	}
}

void draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int color;
	
	x = 0;
	y = 0;

	t_img	img;
	
	void *mlx = mlx_init();
	// if (!mlx)
	// {
	// 	fprintf(stderr, "Error: Failed to initialize MLX.\n"); exit(EXIT_FAILURE);
	// }
	
	void *win = mlx_new_window(mlx, 800, 800, "minimap");
	// if (!win)
	// {	// destroy image, window, display, free, exit
	// 	fprintf(stderr, "Error: Failed to create window.\n"); exit(EXIT_FAILURE);
	// }
	
	img.img_ptr = mlx_new_image(mlx, 800, 800);
	// if(!img.img_ptr)
	// {
	// 	fprintf(stderr, "Error: Failed to create image.\n"); mlx_destroy_window(mlx, win); exit(EXIT_FAILURE);
	// }
	
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bbp, &img.line_length,
		&img.endian);
	
	while (y < data->map_height)
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1') // wall
				color = 0xbe5ac4;
			else if (data->map[y][x] == '0') // not wall
				color = 0xE7BCB4;
			else // player
				color = 0x701C1C;
			int i = x * 10;
			int j = y * 10;
			while (i <= (x + 1) * 10)
			{
				while (j <= (y + 1) * 10)
					put_pixel_to_img(mlx, &img, i, j++, color);
				i++;
				j = y * 10;
			}
			x++;
		}
		y++;
		x = 0;
	}
	mlx_put_image_to_window(mlx, win, img.img_ptr, 0, 0);
	mlx_loop(mlx);
}
