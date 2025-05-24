/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:50:38 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/22 00:51:35 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
takes my_game struct pointer and calculates ray directions pased on
camera plane that we have given (field of View but in vector format)
It casts a ray for each column x on the screen for [0, screen_width -1]
camera_x range -> range [-1.0, 1.0]
*/
void	render_map(my_game *game)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;

	x = -1;
	// printf("0 img->image = %p\n", ((t_img*)(game->texture_img[0]))->image);
    // printf("1 img->image = %p\n", ((t_img*)(game->texture_img[1]))->image); 
    // printf("2 img->image = %p\n", ((t_img*)(game->texture_img[2]))->image); 
    // printf("BEFORE 3 img->image = %p\n", ((t_img*)(game->texture_img[3]))->image);  
	while (++x < SCREEN_WIDTH)
	{
		camera_x = 2.0 * (double)x / (double)SCREEN_WIDTH - 1.0;
		ray_dir_x = game->player_dir_x + game->plane_x * camera_x;
		ray_dir_y = game->player_dir_y + game->plane_y * camera_x;
		cast_ray(game, ray_dir_x, ray_dir_y, x);
		if (x == SCREEN_WIDTH - 1)
		{
			// printf("0 img->image = %p\n", ((t_img*)(game->texture_img[0]))->image);
			// printf("1 img->image = %p\n", ((t_img*)(game->texture_img[1]))->image); 
			// printf("2 img->image = %p\n", ((t_img*)(game->texture_img[2]))->image); 
			// printf("DURING 3 img->image = %p\n", ((t_img*)(game->texture_img[3]))->image);
		}
	}
	//forsprites
	handle_sprites(game);
	draw_minimap(game);
	
	// printf("0 img->image = %p\n", ((t_img*)(game->texture_img[0]))->image);
	// printf("1 img->image = %p\n", ((t_img*)(game->texture_img[1]))->image); 
	// printf("2 img->image = %p\n", ((t_img*)(game->texture_img[2]))->image); 
	// printf("AFTER 3 img->image = %p\n", ((t_img*)(game->texture_img[3]))->image);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img_ptr, 0, 0);
}
