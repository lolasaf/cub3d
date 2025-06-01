/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:48:34 by wel-safa          #+#    #+#             */
/*   Updated: 2025/06/01 20:49:16 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_texture(t_ray *ray, t_draw *draw_vars)
{
	if (ray->side == HORIZONTAL)
	{
		if (ray->dir_y > 0)
			draw_vars->texture = TEX_SOUTH;
		else
			draw_vars->texture = TEX_NORTH;
	}
	else
	{
		if (ray->dir_x > 0)
			draw_vars->texture = TEX_WEST;
		else
			draw_vars->texture = TEX_EAST;
	}
}

void	calculate_wall_x(t_game *game, t_ray *ray, t_draw *draw_vars)
{
	if (ray->side == HORIZONTAL)
		draw_vars->wall_x = game->player_x + ray->perp_distance * ray->dir_x;
	else
		draw_vars->wall_x = game->player_y + ray->perp_distance * ray->dir_y;
	draw_vars->wall_x -= floor(draw_vars->wall_x);
	if (draw_vars->wall_x < 0.0)
		draw_vars->wall_x = 0.0;
	if (draw_vars->wall_x > 1.0)
		draw_vars->wall_x = 1.0;
}

int	get_tex_x(t_game *game, t_draw *draw_vars)
{
	int	tex_x;

	tex_x = (int)(draw_vars->wall_x
			* game->conf->o->tex_width[draw_vars->texture]);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= game->conf->o->tex_width[draw_vars->texture])
		tex_x = game->conf->o->tex_width[draw_vars->texture] - 1;
	return (tex_x);
}

int scale_color(int color, double factor)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color >> 16) & 0xFF) * factor);
	g = (int)(((color >> 8) & 0xFF) * factor);
	b = (int)((color & 0xFF) * factor);
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
	return ((r << 16) | (g << 8) | b);
}

void	draw_wall_column(t_game *game, t_draw *draw_vars, int tex_x, t_ray *ray)
{
	int				y;
	int				tex_y;
	unsigned int	*txt_addr;
	int				color;

	y = draw_vars->draw_start;
	while (y <= draw_vars->draw_end)
	{
		tex_y = ((y - draw_vars->og_draw_start) * 
				game->conf->o->tex_height[draw_vars->texture])
			/ draw_vars->wall_height;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= game->conf->o->tex_height[draw_vars->texture])
			tex_y = game->conf->o->tex_height[draw_vars->texture] - 1;
		txt_addr = game->conf->o->texture_addr[draw_vars->texture];
		color = txt_addr[tex_y * game->conf->o->texture_ll[draw_vars->texture] 
			/ 4 + tex_x];
		double brightness = 1.0 / (1.0 + ray->perp_distance * 0.2);
		if (brightness < 0.2)
		 	brightness = 0.2;
		color = scale_color(color, brightness);
		put_pixel_to_img(game, draw_vars->col, y, color);
		y++;
	}
}

void	draw_wall(t_game *game, t_ray *ray, t_draw *draw_vars)
{
	int	tex_x;

	assign_texture(ray, draw_vars);
	calculate_wall_x(game, ray, draw_vars);
	tex_x = get_tex_x(game, draw_vars);
	draw_wall_column(game, draw_vars, tex_x, ray);
}
