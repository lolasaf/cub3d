/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:09:40 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/18 21:52:48 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_minimap(my_game *game)
{
	int	x;
	int	y;
	int color;
	int px;
	int py;
	int scale;
	int	i, j;
	x = 0;
	y = 0;
	scale = 5;	
	while (y < game->conf->map_height)
	{
		while (game->conf->map[y][x])
		{
			if (game->conf->map[y][x] == '1') // wall
				color = 0x222222;
			else
				color = 0xCCCCCC; // floor

			int i = x * scale;
			int j = y * scale;
			while (i <= (x + 1) * scale)
			{
				while (j <= (y + 1) * scale)
					put_pixel_to_img(game->mlx, game->img, i, j++, color);
				i++;
				j = y * scale;
			}
			x++;
		}
		y++;
		x = 0;
	}
	
	px = (int)(game->player_x * scale);
    py = (int)(game->player_y * scale);
	j = py - 2;
	while (j <= py + 2)
	{
		i = px - 2;
		while (i <= px + 2)
		{
			put_pixel_to_img(game->mlx, game->img, i, j, 0xFFFF00); // player color
			i++;
		}
		j++;
	}
}
