/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:25:54 by kforfoli          #+#    #+#             */
/*   Updated: 2025/05/18 22:22:28 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_esc(my_game *game)
{
	mlx_destroy_image(game->mlx, game->img->img_ptr);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit (1);
}

void isnot_wall(my_game *game, double x, double y)
{
    if (game->conf->map[(int)y][(int)x] != '\0' && game->conf->map[(int)y][(int)x] != '1')
    {
        game->player_x = x;
        game->player_y = y;
    }
    else
        return;   
}

int handle_keypress(int kc, my_game *game)
{
    double move_speed = 0.1;
    double rot_speed = 0.05;

    if (kc == ESC_KEY)
		handle_esc(game);
    if (kc == W_KEY)
    {
        double new_x = game->player_x + game->player_dir_x * move_speed;
        double new_y = game->player_y + game->player_dir_y * move_speed;
        isnot_wall(game, new_x, new_y);
    } 
    else if (kc == S_KEY)
    {
        double new_x = game->player_x - game->player_dir_x * move_speed;
        double new_y = game->player_y - game->player_dir_y * move_speed;
        isnot_wall(game, new_x, new_y);
    }
    else if (kc == A_KEY)
    {
        double new_x = game->player_x + game->player_dir_y * move_speed;
        double new_y = game->player_y - game->player_dir_x * move_speed;
        isnot_wall(game, new_x, new_y);
        }
    else if (kc == D_KEY)
    {
        double new_x = game->player_x - game->player_dir_y * move_speed;
        double new_y = game->player_y + game->player_dir_x * move_speed;
        isnot_wall(game, new_x, new_y);        
    }
    else if (kc == RIGHT_ARROW)
    {
        //for direction vector
        double old_dir_x = game->player_dir_x;
        game->player_dir_x = game->player_dir_x * cos(rot_speed) - game->player_dir_y * sin(rot_speed);
        game->player_dir_y = old_dir_x * sin(rot_speed) + game->player_dir_y * cos(rot_speed);
        //for camera plane
        double old_plane_x = game->plane_x;
        game->plane_x = game->plane_x * cos(rot_speed) - game->plane_y * sin(rot_speed);
        game->plane_y = old_plane_x * sin(rot_speed) + game->plane_y * cos(-rot_speed);
    }
    else if (kc == LEFT_ARROW)
    {
        double old_dir_x = game->player_dir_x;
        game->player_dir_x = game->player_dir_x * cos(-rot_speed) - game->player_dir_y * sin(-rot_speed);
        game->player_dir_y = old_dir_x * sin(-rot_speed) + game->player_dir_y * cos(-rot_speed);

        double old_plane_x = game->plane_x;
        game->plane_x = game->plane_x * cos(-rot_speed) - game->plane_y * sin(-rot_speed);
        game->plane_y = old_plane_x * sin(-rot_speed) + game->plane_y * cos(-rot_speed);
    }
    clear_image(game->img);
    render_map(game); // Redraw the scene
    //mlx_put_image_to_window(game->mlx, game->win, game->img->img_ptr, 0, 0);
    // clear_image(game->img);
    return 0;
}
