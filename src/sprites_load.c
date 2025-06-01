/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:26:19 by wel-safa          #+#    #+#             */
/*   Updated: 2025/06/01 23:08:39 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_sprite_num(t_game *g)
{
	g->num_sprites = ft_counter(g) / SPRITE_RATIO;
	if (g->num_sprites == 0)
		g->num_sprites = 1;
	if (g->num_sprites > 4)
		g->num_sprites = 4;
}

int	fake_random(int seed, int a, int b)
{
	double	x;
	double	frac;
	int		range;

	x = sin(seed * 12.9898) * 43758.5453;
	frac = x - floor(x);
	range = b - a + 1;
	return (a + (int)(fabs(frac) * range));
}

void	mlx_sprite_load(t_game *g)
{
	int			i;
	int			w;
	int			h;
	int			j;
	const char	*sprite_paths[SPRITE_LOAD] = {"sprites/charizard.xpm",
		"sprites/dragonair.xpm", "sprites/eevee.xpm", "sprites/horsea.xpm",
		"sprites/mewtwo.xpm", "sprites/raikou.xpm", "sprites/wigglytuff.xpm"};

	get_sprite_num(g);
	i = 0;
	while (i < g->num_sprites)
	{
		j = i;
		if (i > 5)
			j = i % SPRITE_LOAD;
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

void	draw_mini_sprite(t_game *game, int px, int py, int scale)
{
	int	i;
	int	j;

	px = (int)(px * scale);
	py = (int)(py * scale);
	j = py - 2;
	while (j <= py + 2)
	{
		i = px - 2;
		while (i <= px + 2)
		{
			put_pixel_to_img(game, i, j, 0xEE4B2B);
			i++;
		}
		j++;
	}
}

void	get_tex_y(int *d, t_img *sprite_tex, t_sprite_props *prop, int *tex_y)
{
	*tex_y = ((*d * sprite_tex->height) / prop->s_h) / 256;
	if (*tex_y < 0)
		*tex_y = 0;
	if (*tex_y >= sprite_tex->height)
		*tex_y = sprite_tex->height - 1;
}
