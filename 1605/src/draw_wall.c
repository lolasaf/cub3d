/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:48:34 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/18 20:18:38 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_texture(t_ray *ray, t_draw *draw_vars)
{
	if (ray->side == 0)
	{
		if (ray->dir_y > 0)
			draw_vars->texture = TEX_NORTH;
		else
			draw_vars->texture = TEX_SOUTH;
	}
	else
	{
		if (ray->dir_x > 0)
			draw_vars->texture = TEX_EAST;
		else
			draw_vars->texture = TEX_WEST;
	}
}

void	calculate_wall_x(my_game *game, t_ray *ray, t_draw *draw_vars)
{
	if (ray->side == 0)
		draw_vars->wall_x = game->player_x + ray->perp_distance * ray->dir_x;
	else
		draw_vars->wall_x = game->player_y + ray->perp_distance * ray->dir_y;
	draw_vars->wall_x -= floor(draw_vars->wall_x);
	if (draw_vars->wall_x < 0.0)
		draw_vars->wall_x = 0.0;
	if (draw_vars->wall_x > 1.0)
		draw_vars->wall_x = 1.0;
}

int	get_tex_x(my_game *game, t_draw *draw_vars)
{
	int	tex_x;

	tex_x = (int)(draw_vars->wall_x * game->conf->o->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= game->conf->o->width)
		tex_x = game->conf->o->width - 1;
	return (tex_x);
}

void	draw_wall_column(my_game *game, t_draw *draw_vars, int tex_x)
{
	int				y;
	int				tex_y;
	unsigned int	*txt_addr;
	int				color;

	y = draw_vars->draw_start;
	while (y <= draw_vars->draw_end)
	{
		tex_y = ((y - draw_vars->og_draw_start) * 
				game->conf->o->height) / draw_vars->wall_height;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= game->conf->o->height)
			tex_y = game->conf->o->height - 1;
		txt_addr = game->conf->o->texture_addr[draw_vars->texture];
		color = txt_addr[tex_y * game->conf->o->texture_ll[draw_vars->texture] 
			/ 4 + tex_x];
		put_pixel_to_img(game->mlx, game->img, draw_vars->col, y, color);
		y++;
	}
}

void	draw_wall(my_game *game, t_ray *ray, t_draw *draw_vars)
{
	int	tex_x;

	assign_texture(ray, draw_vars);
	calculate_wall_x(game, ray, draw_vars);
	tex_x = get_tex_x(game, draw_vars);
	draw_wall_column(game, draw_vars, tex_x);
}
