/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:29:43 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/30 01:50:08 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_sprite_pixel_color(t_img *sprite_tex, int tex_x, int tex_y)
{
	unsigned int	*tex_addr;
	int				tex_ll;

	tex_addr = (unsigned int *)sprite_tex->data;
	tex_ll = sprite_tex->size_line;
	if (tex_x < 0 || tex_x >= sprite_tex->width || tex_y < 0
		|| tex_y >= sprite_tex->height)
		return (0x0);
	return (tex_addr[tex_y * (tex_ll / 4) + tex_x]);
}

void	draw_stripe(my_game *game, t_img *sprite_tex, t_sprite_props *prop,
		int tex_x)
{
	int				y;
	int				tex_y;
	unsigned int	color;
	int				d;

	y = prop->start_y;
	while (y < prop->end_y)
	{
		d = (y) * 256 - SCREEN_HEIGHT * 128 + prop->s_h * 128;
		tex_y = ((d * sprite_tex->height) / prop->s_h) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= sprite_tex->height)
			tex_y = sprite_tex->height - 1;
		color = get_sprite_pixel_color(sprite_tex, tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0)
			put_pixel_to_img(game, prop->stripe_x, y, color);
		y++;
	}
}

void	single_sprite_render(my_game *g, t_img *sprite_tex,
		t_sprite_props *prop)
{
	int	tex_x;

	prop->stripe_x = prop->start_x;
	while (prop->stripe_x < prop->end_x)
	{
		if (prop->stripe_x >= 0 && prop->stripe_x < SCREEN_WIDTH
			&& prop->t_y < g->z_buffer[prop->stripe_x])
		{
			tex_x = (int)(256 * (prop->stripe_x - (-prop->s_w / 2 + prop->s_sx))
					* sprite_tex->width / prop->s_w) / 256;
			if (tex_x < 0)
				tex_x = 0;
			if (tex_x >= sprite_tex->width)
				tex_x = sprite_tex->width - 1;
			draw_stripe(g, sprite_tex, prop, tex_x);
		}
		prop->stripe_x++;
	}
}

void	render_sprites(sprite_sort *to_sort, my_game *g)
{
	int				i;
	t_sprite		*s;
	t_img			*sprite_tex;
	t_sprite_props	prop;
	double			catch;

	i = 0;
	while (i < g->num_sprites)
	{
		s = &g->sprites[to_sort[i].index];
		sprite_tex = (t_img *)g->sprites[s->id].img;
		if (!sprite_tex)
		{
			i++;
			continue ;
		}
		prop = calc_properties(g, s, &catch);
		if (prop.t_y <= 0.0 || prop.t_y < 0.01)
		{
			i++;
			continue ;
		}
		single_sprite_render(g, sprite_tex, &prop);
		i++;
	}
}

void	handle_sprites(my_game *g)
{
	sprite_sort	to_sort[MAX_SPRITES];
	int			i;

	i = 0;
	while (i < g->num_sprites)
	{
		to_sort[i].dist = ((g->player_x - g->sprites[i].x) * (g->player_x
					- g->sprites[i].x)) + ((g->player_y - g->sprites[i].y)
				* (g->player_y - g->sprites[i].y));
		to_sort[i].index = i;
		i++;
	}
	ft_sort(to_sort, g->num_sprites);
	render_sprites(to_sort, g);
}
