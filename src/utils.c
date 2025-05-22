/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:01:22 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/22 00:31:23 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	clear_image(t_imgp *img)
// {
// 	memset(img->addr, 0, img->line_length * SCREEN_HEIGHT);
// }

void	clear_image(my_game *game, t_imgp *img)
{
	int px = -1;
	int py = -1;
	while (++px < SCREEN_WIDTH)
	{
		py = -1;
		while (++py < SCREEN_HEIGHT)
			put_pixel_to_img(game->mlx, img, px, py, 0);
	}
}

/*
Puts pixel on image at coordinates (x, y)
If bits per pixel is not 32, we call mlx_get_color_value to translate color
to fit the bits per pixel requirement of the image.
The bits position depends on the computer's endian,
bits are assigned accordingly.
*/
void	put_pixel_to_img(void *mlx, t_imgp *img, int x, int y, int color)
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
