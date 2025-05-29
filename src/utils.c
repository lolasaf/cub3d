/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:18:02 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/30 01:07:34 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	err_msg(const char *msg, void *build, void *data)
{
	free_build((t_build *)build);
	free_map((t_data *)data);
	free_texture_vars((t_data *)data);
	free_gnl_buffer();
	printf("$Error: %s\n", msg);
	exit(1);
}

void	clear_image(t_game *game)
{
	int	px;
	int	py;

	px = -1;
	py = -1;
	while (++px < SCREEN_WIDTH)
	{
		py = -1;
		while (++py < SCREEN_HEIGHT)
			put_pixel_to_img(game, px, py, 0);
	}
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

/*
Puts pixel on image at coordinates (x, y)
If bits per pixel is not 32, we call mlx_get_color_value to translate color
to fit the bits per pixel requirement of the image.
The bits position depends on the computer's endian,
bits are assigned accordingly.
*/
void	put_pixel_to_img(t_game *game, int x, int y, int color)
{
	int		pixel;
	void	*mlx;
	t_imgp	*img;

	mlx = game->mlx;
	img = game->img;
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

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f')
		return (1);
	return (0);
}
