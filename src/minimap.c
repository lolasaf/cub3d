/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:09:40 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/18 22:32:45 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_mini_player(my_game *game, int scale)
{
	int	px;
	int	py;
	int	i;
	int	j;

	px = (int)(game->player_x * scale);
	py = (int)(game->player_y * scale);
	j = py - 2;
	while (j <= py + 2)
	{
		i = px - 2;
		while (i <= px + 2)
		{
			put_pixel_to_img(game->mlx, game->img, i, j, 0xFFFF00);
			i++;
		}
		j++;
	}
}

void	draw_mini_grid(my_game *game, int scale, int x, int y)
{
	int	i;
	int	j;
	int	color;

	if (game->conf->map[y][x] == '1')
		color = 0x222222;
	else
		color = 0xCCCCCC;
	i = x * scale;
	j = y * scale;
	while (i <= (x + 1) * scale)
	{
		while (j <= (y + 1) * scale)
			put_pixel_to_img(game->mlx, game->img, i, j++, color);
		i++;
		j = y * scale;
	}
}

void	draw_minimap(my_game *game)
{
	int	x;
	int	y;
	int	scale;

	x = 0;
	y = 0;
	scale = 5;
	while (y < game->conf->map_height)
	{
		while (game->conf->map[y][x])
		{
			draw_mini_grid(game, scale, x, y);
			x++;
		}
		y++;
		x = 0;
	}
	draw_mini_player(game, scale);
}
