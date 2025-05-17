/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:50:38 by wel-safa          #+#    #+#             */
/*   Updated: 2025/04/29 15:01:46 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
takes my_game struct pointer and calculates ray directions pased on
camera plane that we have given (field of View but in vector format)
*/
void	render_map(my_game *game)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		// cast a ray for each column x on the screen for [0, screen_width -1]
		// camera_x range  // range [-1.0, 1.0]
		camera_x = 2.0 * (double)x / (double)SCREEN_WIDTH - 1.0;
		ray_dir_x = game->player_dir_x + game->plane_x * camera_x;
		ray_dir_y = game->player_dir_y + game->plane_y * camera_x;
		cast_ray(game, ray_dir_x, ray_dir_y, x);
	}
}
