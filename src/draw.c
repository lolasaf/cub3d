/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:11:24 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/18 21:47:25 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int rgb_to_hex(int r, int g, int b)
{
	if (r > 255 || g > 255 || b > 255)
		return 0x000000;
	int hex_color = (r << 16) | (g << 8) | b;
	return hex_color;
}

void draw_ceiling(my_game *game, t_draw *draw_vars)
{
	int hex_c;
	int y;

	hex_c = rgb_to_hex(game->conf->color[1].rgb[0], game->conf->color[1].rgb[1], game->conf->color[1].rgb[2]);
	y = draw_vars->draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		put_pixel_to_img(game->mlx, game->img, draw_vars->col, y, hex_c);
		y++;
	}
}

void draw_floor(my_game *game, t_draw *draw_vars)
{
	int hex_f;
	int y;

	hex_f = rgb_to_hex(game->conf->color[0].rgb[0], game->conf->color[0].rgb[1], game->conf->color[0].rgb[2]);
	y = 0;	
	while(y < draw_vars->draw_start)
	{
		put_pixel_to_img(game->mlx, game->img, draw_vars->col, y, hex_f);
		y++;
	}
}
void	get_draw_vars(t_ray *ray, t_draw *draw_vars)
{
	if (!isfinite(ray->perp_distance) || ray->perp_distance <= 1e-6)
		ray->perp_distance = 1e-6;
	draw_vars->wall_height = (int) (SCREEN_HEIGHT / ray->perp_distance);
	draw_vars->og_draw_start = SCREEN_HEIGHT / 2 - draw_vars->wall_height / 2;
	draw_vars->draw_start = draw_vars->og_draw_start;
	if (draw_vars->draw_start < 0)
		draw_vars->draw_start = 0;
	draw_vars->draw_end = SCREEN_HEIGHT / 2 + draw_vars->wall_height / 2;
	if (draw_vars->draw_end >= SCREEN_HEIGHT)
		draw_vars->draw_end = SCREEN_HEIGHT - 1;
}

void	draw(my_game *game, t_draw *draw_vars, t_ray *ray)
{
	get_draw_vars(ray, draw_vars);
	draw_wall(game, ray, draw_vars);
	draw_floor(game, draw_vars);
	draw_ceiling(game, draw_vars);
	//mlx_put_image_to_window(game->mlx, game->win, game->img->img_ptr, 0, 0);
}
