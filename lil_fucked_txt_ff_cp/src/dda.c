/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:11:24 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/09 21:09:55 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
normalizes vector by dividing x and y by length of vector
*/
void	normalize_vector(double *x, double *y)
{
	double length;

	length = sqrt(*x * *x + *y * *y);
	if (length != 0)
	{
		*x /= length;
		*y /= length;
	}
}

/*
Given a player position and ray direction,
this function gives us the next intersection with a grid line of a given ray
*/
void	next_intersection(t_ray *ray)
{
	if (fabs(ray->hit_x - round(ray->hit_x)) < 1e-6)
	{
		// Already on gridline
		if (ray->dir_x > 0)
			ray->step_x = 1.0 / ray->dir_x;
		else if (ray->dir_x < 0)
			ray->step_x = 1.0 / -ray->dir_x;
		else
			ray->step_x = INFINITY;
	}
	else
	{
		//printf("hit_x = %f, ceil(hit_x) = %f\n", ray->hit_x, ceil(ray->hit_x));
		if (ray->dir_x < 0) // dx < 0
			ray->step_x = (floor(ray->hit_x) - ray->hit_x) / ray->dir_x;
		else if (ray->dir_x > 0) // dx > 0
			ray->step_x = (ceil(ray->hit_x) - ray->hit_x) / ray->dir_x;
		else // dx = 0
			ray->step_x = INFINITY;
	}

	// if (ray->dir_x < 0) // dx < 0
	// 	ray->step_x = (floor(ray->hit_x) - ray->hit_x) / ray->dir_x;
	// else if (ray->dir_x > 0) // dx > 0
	// 	ray->step_x = (ceil(ray->hit_x) - ray->hit_x) / ray->dir_x;
	// else // dx = 0
	// 	ray->step_x = INFINITY;

	if (fabs(ray->hit_y - round(ray->hit_y)) < 1e-6)
	{
		// Already on gridline
		if (ray->dir_y > 0)
			ray->step_y = 1.0 / ray->dir_y;
		else if (ray->dir_y < 0)
			ray->step_y = 1.0 / -ray->dir_y;
		else
			ray->step_y = INFINITY;
	}
	else
	{
		if (ray->dir_y < 0) // dy < 0
			ray->step_y = (floor(ray->hit_y) - ray->hit_y) / ray->dir_y;
		else if (ray->dir_y > 0) // dy > 0
			ray->step_y = (ceill(ray->hit_y) - ray->hit_y) / ray->dir_y;
		else // dy = 0;
			ray->step_y = INFINITY;
	}
	ray->hit_x += ray->dir_x * (fmin(ray->step_x, ray->step_y));
	ray->hit_y += ray->dir_y * (fmin(ray->step_x, ray->step_y));	
	ray->map_x = (int) ray->hit_x;
	ray->map_y = (int) ray->hit_y;
	if (ray->step_x < ray->step_y)
		ray->side = 1; // vertical wall
	else
		ray->side = 0; // horizental wall
}

void	compute_distance(my_game *game, t_ray *ray)
{
	double	real_distance;
	double	cos_correct;
	double	ray_dir_x;
	double	ray_dir_y;

	if (ray->side == 0) // horizental gridline intersection -> hitting Y gridline
		real_distance = (ray->hit_y - game->player_y) / ray->dir_y;
	else // vertical gridline intersection -> hitting X gridline
		real_distance = (ray->hit_x - game->player_x) / ray->dir_x;
	ray_dir_x = ray->dir_x;
	ray_dir_y = ray->dir_y;
	normalize_vector(&(ray_dir_x), &(ray_dir_y));
	cos_correct = (ray_dir_x * game->player_dir_x) + (ray_dir_y * game->player_dir_y);
	ray->perp_distance = real_distance * cos_correct;
}

int rgb_to_hex(int r, int g, int b)
{
	if (r > 255 || g > 255 || b > 255)
		return 0x000000;
	int hex_color = (r << 16) | (g << 8) | b;
	return hex_color;
}


void	draw_wall(my_game *game, int col, t_ray *ray)
{
	int wall_height;
	int draw_start;
	int draw_end;
	int color;

	wall_height = (int) (SCREEN_HEIGHT / ray->perp_distance);
	draw_start = SCREEN_HEIGHT / 2 - wall_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = SCREEN_HEIGHT / 2 + wall_height / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	// void	put_pixel_to_img(void *mlx, t_img *img, int x, int y, int color)

	// TEXTURE CODE
	/*
	int texture;
	if (ray->side == 0)
	{
		if (ray->dir_y > 0)
			texture = 0;
		else
			texture = 1;
	}
	else
	{
		if(ray->dir_x > 0)
			texture = 2;
		else
			texture = 3;
	}
	double wall_x;
	if (ray->side == 0)
			wall_x = game->player_x + ray->perp_distance * ray->dir_x;
	else
			wall_x = game->player_y + ray->perp_distance * ray->dir_y;
	wall_x -= floor(wall_x);
	int tex_x = (int)(wall_x * game->conf->o->width);
	if (tex_x < 0)
			tex_x = 0;
	if (tex_x >= game->conf->o->width)
			tex_x = game->conf->o->width - 1;

	for (int y = draw_start; y <= draw_end; y++) {
        int tex_y = (((y - draw_start) * game->conf->o->height) /
                     wall_height); // Calculate texture y-coordinate
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= game->conf->o->height)
            tex_y = game->conf->o->height - 1;
        // Get color from texture
        unsigned int *txt_addr = game->conf->o->texture_addr[texture];
        int color = txt_addr[tex_y * game->conf->o->texture_ll[texture] / 4 +  tex_x];
        put_pixel_to_img(game->mlx, game->img, col, y, color);
    }

	int hex_f  = rgb_to_hex(game->conf->color[0].rgb[0], game->conf->color[0].rgb[1], game->conf->color[0].rgb[2]);
	//printf("%d\n", hex_f);
	int hex_c = rgb_to_hex(game->conf->color[1].rgb[0], game->conf->color[1].rgb[1], game->conf->color[1].rgb[2]);
	//printf("%d\n", hex_c);
	int y = 0;
	while(y <= draw_start)
	{
		put_pixel_to_img(game->mlx, game->img, col, y, hex_f);
		y++;
	}
	y = draw_end;
	while (y <= SCREEN_HEIGHT)
	{
		put_pixel_to_img(game->mlx, game->img, col, y, hex_c);
		y++;
	}
*/

	// COLOR CODE
	int i = 0;
	i = draw_start;
	while (i <= draw_end)
	{
		if (ray->side == 0) // horizental
			color = 0xFFAAAA;
		else
			color = 0xAA5555; // vertical
		put_pixel_to_img(game->mlx, game->img, col, i, color);
		i++;
	}
	
	// below needs to be tested
	int y = 0;
	while(y <= draw_start)
	{
		put_pixel_to_img(game->mlx, game->img, col, y, 0x88CCEE);
		y++;
	}
	y = draw_end;
	while (y <= SCREEN_HEIGHT)
	{
		put_pixel_to_img(game->mlx, game->img, col, y, 0x88FF88);
		y++;
	}


	
	//printf("Ray hit at (%.2f, %.2f) distance %.2f wall height %d\n ", ray->hit_x, ray->hit_y, ray->perp_distance, wall_height);
}

void	cast_ray(my_game *game, double ray_dir_x, double ray_dir_y, int col)
{
	t_ray ray;
	
	// printf("map_height from struct: %d\n", game->conf->map_height);
	// printf("map width from struct: %d\n", game->conf->map_width);
	ray.hit = 0;
	ray.dir_x = ray_dir_x;
	ray.dir_y = ray_dir_y;
	ray.hit_x = game->player_x;
	ray.hit_y = game->player_y;
	ray.step_x = 0;
	ray.step_y = 0;
	ray.map_x = (int)game->player_x;
	ray.map_y = (int)game->player_y;
	while (!ray.hit)
	{

		next_intersection(&ray);
		if (ray.dir_x < 0 && ray.side == 1)
			ray.map_x += -1; // adjust for lower x if coming from left to right
		else if (ray.dir_y < 0 && ray.side == 0)
			ray.map_y += -1; // adjust for lower y if coming from down up
		if (ray.map_x >= 0 && ray.map_x < game->conf->map_width &&
				ray.map_y >= 0 && ray.map_y < game->conf->map_height)
		{
			if (game->conf->map[(int)ray.map_y][(int)ray.map_x] == '1')
			{
				ray.hit = 1;
				break;
			}
				// ray.hit = 1;
			// printf("HERE\n");
			// printf("RAY_MAP_X: %d\n", ray.map_x);
			// printf("RAY_MAP_Y: %d\n", ray.map_y);
			// printf("MAP_WIDTH: %d\n", game->conf->map_width);
			// printf("MAP_HEIGHT: %d\n", game->conf->map_height);
			// printf("map value: %c\n", game->conf->map[ray.map_y][ray.map_x]);
		}
		else
			ray.hit = 1;
			// ray.hit = 0; // treat out of bounds as wall
	}
	compute_distance(game, &ray);
	draw_wall(game, col, &ray);
}
