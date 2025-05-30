/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:54:11 by kforfoli          #+#    #+#             */
/*   Updated: 2025/05/30 20:23:16 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_counter(t_game *g)
{
	int	x;
	int	y;
	int	c;

	y = 0;
	c = 0;
	while (y < g->conf->map_height)
	{
		x = 0;
		while (g->conf->map[y][x])
		{
			if (g->conf->map[y][x] == 'X')
				c++;
			x++;
		}
		y++;
	}
	return (c);
}

void	ft_check(double *b_x, double *b_y, t_game *g, char c)
{
	if (c == 's')
	{
		if (*b_x < 0 || (int)*b_x >= g->conf->map_width)
			*b_x = (g->conf->map_width / 2) + 0.5;
		if (*b_y < 0 || (int)*b_y >= g->conf->map_height)
			*b_y = (g->conf->map_height / 2) + 0.5;
	}
	else
	{
		if (*b_x < 0 || (int)*b_x >= g->conf->map_width)
			*b_x = 0.5;
		if (*b_y < 0 || (int)*b_y >= g->conf->map_height)
			*b_y = 0.5;
	}
}

int	ft_set(double *b_x, double *b_y, t_game *g, int i)
{
	if (g->conf->map[(int)*b_y][(int)*b_x] == 'X')
	{
		g->sprites[i].x = *b_x;
		g->sprites[i].y = *b_y;
		g->sprites[i].id = i;
		*b_x = fake_random(i * 2, 0, g->conf->map_width - 1) + 0.5;
		*b_y = fake_random(i * 2 + 1, 0, g->conf->map_height - 1) + 0.5;
		return (0);
	}
	return (1);
}

void	ft_init_sprites(t_game *g)
{
	int		i;
	double	b_x;
	double	b_y;

	i = 0;
	while (i < g->num_sprites)
	{
		b_x = fake_random(i * 2, 0, g->conf->map_width - 1) + 0.5;
		b_y = fake_random(i * 2 + 1, 0, g->conf->map_height - 1) + 0.5;
		ft_check(&b_x, &b_y, g, 's');
		while (1)
		{
			if (ft_set(&b_x, &b_y, g, i) == 0)
				break ;
			else
			{
				b_x++;
				b_y++;
				ft_check(&b_x, &b_y, g, 'e');
			}
		}
		i++;
	}
}

void	general_destroy(t_game *g)
{
	free_textures(g);
	free_sprites(g);
	destroy_mlx(g);
	destroy_buffer(g);
	err_msg("Failed to load sprites!", g->conf->build, g->conf);
}
