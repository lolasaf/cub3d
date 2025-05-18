/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:16:10 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/18 19:47:24 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	compute_distance(my_game *game, t_ray *ray)
{
	if (ray->side == 0 ) // horizontal wall
	{
		if (fabs(ray->dir_y) < 1e-6) // checking for dir_y close to zero
		{
			ray->perp_distance = INFINITY;
			return;
		}
		ray->perp_distance = (ray->map_y - game->player_y + (1 - ray->step_y) / 2.0) / ray->dir_y;
	}
	else // vertical wall
	{
		if (fabs(ray->dir_x) < 1e-6)
		{
			ray->perp_distance = INFINITY;
			return;
		}
		ray->perp_distance = (ray->map_x - game->player_x + (1 - ray->step_x) / 2.0) / ray->dir_x;
	}
	ray->hit_x = game->player_x + ray->perp_distance * ray->dir_x;
	ray->hit_y = game->player_y + ray->perp_distance * ray->dir_y;
}

void	calc_steps(my_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player_y) * ray->delta_dist_y;
	}
}

void	init_ray(my_game *game, t_ray *ray)
{
	ray->map_x = (int)game->player_x;
	ray->map_y = (int)game->player_y;
	ray->hit = 0;
	if (ray->dir_x == 0)
		ray->delta_dist_x = INFINITY;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = INFINITY;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
	calc_steps(game, ray);
}

void	ray_loop(my_game *game, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 1; // vertical wall
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 0; // horizontal wall
		}
		if (ray->map_x >= 0 && ray->map_x < game->conf->map_width &&
			ray->map_y >= 0 && ray->map_y < game->conf->map_height)
		{
			if (game->conf->map[ray->map_y][ray->map_x] == '1')
				ray->hit = 1;
		}
		else
			ray->hit = 1; // out of bounds
	}
}

void	cast_ray(my_game *game, double ray_dir_x, double ray_dir_y, int col)
{
	t_ray ray;
	t_draw draw_vars;
	ray.dir_x = ray_dir_x;
	ray.dir_y = ray_dir_y;
	draw_vars.col = col;
	init_ray(game, &ray);
	ray_loop(game, &ray);
	compute_distance(game, &ray);
	draw(game, &draw_vars, &ray);
}
