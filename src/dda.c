/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:11:24 by wel-safa          #+#    #+#             */
/*   Updated: 2025/04/27 02:09:14 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Given a player position and ray direction,
this function gives us the next intersection with a grid line of a given ray
*/
void	nextIntersection(my_game *game, t_ray *ray)
{
	if (ray->dirX < 0) // dx < 0
		ray->stepX = (floorf(ray->hitX) - ray->hitX) / ray->dirX;
	else if (ray->dirX > 0) // dx > 0
		ray->stepX = (ceilf(ray->hitX) - ray->hitX) / ray->dirX;
	else // dx = 0
		ray->stepX = INFINITY;
	if (ray->dirY < 0) // dy < 0
		ray->stepY = (floorf(ray->hitY) - ray->hitY) / ray->dirY;
	else if (ray->dirY > 0) // dy > 0
		ray->stepY = (ceilf(ray->hitY) - ray->hitY) / ray->dirY;
	else // dy = 0;
		ray->stepY = INFINITY;
	ray->hitX += ray->dirX * (fminf(ray->stepX, ray->stepY));
	ray->hitY += ray->dirY * (fminf(ray->stepX, ray->stepY));
	ray->mapX = (int) ray->hitX;
	ray->mapY = (int) ray->hitY;
	if (ray->stepX < ray->stepY)
		ray->side = 1; // vertical wall
	else
		ray->side = 0; // horizental wall
}


void castRay(my_game *game, double rayDirX, double rayDirY)
{
	t_ray ray;
	
	ray.hit = 0;
	ray.dirX = rayDirX;
	ray.dirY = rayDirY;
	ray.hitX = game->playerX;
	ray.hitY = game->playerY;
	while (!ray.hit)
	{
		nextIntersection(game, &ray);
		if (ray.dirX < 0 && ray.side == 1)
			ray.mapX += -1; // adjust for lower x if coming from left to right
		else if (ray.dirY < 0 && ray.side == 0)
			ray.mapY += -1; // adjust for lower y if coming from down up
		
		if (ray.mapX >= 0 && ray.mapX < game->conf->mapWidth &&
				ray.mapY >= 0 && ray.mapY < game->conf->mapHeight)
		{
			if (game->conf->map[ray.mapY][ray.mapX] > 0)
				ray.hit = 1;
		}
		else
			ray.hit = 1; // treat out of bounds as wall
	}
}

/*
*/
void renderWalls(my_game *game)
{
	int		x;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;

	x = -1;
	while(++x < SCREEN_WIDTH)
	{
		// cast a ray for each column x on the screen for [0, screen_width -1]
		cameraX = 2 * x / SCREEN_WIDTH - 1; // range [-1.0, 1.0]
		rayDirX = game->playerDirX + game->planeX * cameraX;
		rayDirY = game->playerDirY + game->planeY * cameraX;
		castRay(game, rayDirX, rayDirY);
		
	}
}