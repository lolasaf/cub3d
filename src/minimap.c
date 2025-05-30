/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:09:40 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/30 21:01:50 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_mini_player(t_game *game, int scale)
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
			put_pixel_to_img(game, i, j, 0xFFFF00);
			i++;
		}
		j++;
	}
}

void	draw_mini_grid(t_game *game, int scale, int x, int y)
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
		if (i < SCREEN_WIDTH && j < SCREEN_HEIGHT)
		{
			while (j <= (y + 1) * scale)
				put_pixel_to_img(game, i, j++, color);
		}
		i++;
		j = y * scale;
	}
}

void	draw_mini_sprites_loop(t_game *game, int scale)
{
	int	i;

	i = 0;
	while (i < game->num_sprites)
	{
		if (game->sprites[i].img)
			draw_mini_sprite(game, game->sprites[i].x,
				game->sprites[i].y, scale);
		i++;
	}
}

int	get_scale(t_game *game)
{
	int		scale;
	double	scale_w;
	double	scale_h;

	scale_w = (SCREEN_WIDTH / 5.0) / game->conf->map_width;
	scale_h = (SCREEN_HEIGHT / 5.0) / game->conf->map_height;
	scale = (int)fmin(scale_w, scale_h);
	if (scale < 1)
		scale = 1;
	return (scale);
}

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;
	int	scale;

	x = 0;
	y = 0;
	scale = get_scale(game);
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
	draw_mini_sprites_loop(game, scale);
}
