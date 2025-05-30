/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:53:02 by kforfoli          #+#    #+#             */
/*   Updated: 2025/05/30 19:25:25 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_sprite_load(t_game *g)
{
	int			i;
	int			w;
	int			h;
	int			j;
	const char	*sprite_paths[8] = {"sprites/charizard.xpm", "sprites/ditto.xpm",
		"sprites/dragonair.xpm", "sprites/eevee.xpm", "sprites/horsea.xpm",
		"sprites/mewtwo.xpm", "sprites/raikou.xpm", "sprites/wigglytuff.xpm"};

	g->num_sprites = ft_counter(g) / 4;
	if (!g->num_sprites)
		g->num_sprites = 1;
	i = 0;
	while (i < g->num_sprites)
	{
		j = i;
		if (i > 5)
			j = i % 8;
		g->sprites[i].img = mlx_xpm_file_to_image(g->mlx,
				(char *)sprite_paths[j], &w, &h);
		if (!g->sprites[i].img)
		{
			g->num_sprites = i + 1;
			general_destroy(g);
		}
		i++;
	}
	ft_init_sprites(g);
}

void	ft_sort(t_sprite_sort *to_sort, int count)
{
	int				i;
	int				j;
	t_sprite_sort	temp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (to_sort[i].dist < to_sort[j].dist)
			{
				temp = to_sort[i];
				to_sort[i] = to_sort[j];
				to_sort[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	get_vertical_prop(t_sprite_props *prop)
{
	prop->s_h = (int)(SCREEN_HEIGHT / prop->t_y);
	prop->start_y = -prop->s_h / 2 + SCREEN_HEIGHT / 2;
	if (prop->start_y < 0)
		prop->start_y = 0;
	prop->end_y = prop->s_h / 2 + SCREEN_HEIGHT / 2;
	if (prop->end_y >= SCREEN_HEIGHT)
		prop->end_y = SCREEN_HEIGHT - 1;
}

void	get_horizonatal_prop(t_sprite_props *prop)
{
	prop->s_w = (int)(SCREEN_HEIGHT / prop->t_y);
	prop->start_x = -prop->s_w / 2 + prop->s_sx;
	if (prop->start_x < 0)
		prop->start_x = 0;
	prop->end_x = prop->s_w / 2 + prop->s_sx;
	if (prop->end_x >= SCREEN_WIDTH)
		prop->end_x = SCREEN_WIDTH - 1;
}

t_sprite_props	calc_properties(t_game *g, t_sprite *s, double *catch)
{
	t_sprite_props	prop;
	double			x_rel;
	double			y_rel;

	x_rel = s->x - g->player_x;
	y_rel = s->y - g->player_y;
	*catch = 1.0 / (g->plane_x * g->player_dir_y - g->player_dir_x
			* g->plane_y);
	if (fabs(*catch) < 1e-6)
		*catch = 1.0;
	prop.t_x = *catch * (g->player_dir_y * x_rel - g->player_dir_x * y_rel);
	prop.t_y = *catch * (-g->plane_y * x_rel + g->plane_x * y_rel);
	prop.s_sx = (int)((SCREEN_WIDTH / 2) * (1 + prop.t_x / prop.t_y));
	get_vertical_prop(&prop);
	get_horizonatal_prop(&prop);
	return (prop);
}
