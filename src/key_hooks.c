/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:25:54 by kforfoli          #+#    #+#             */
/*   Updated: 2025/05/24 03:53:22 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_texture_vars(my_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->conf->texture[i].path)
			free(game->conf->texture[i].path);
        if (game->conf->texture[i].identifier)
            free(game->conf->texture[i].identifier);
		i++;
	}
}

void    free_textures(my_game *game)
{
    int i = 3;

    free_texture_vars(game);
    while (i >= 0)
    {
        if (game->texture_img[i])
        {
            mlx_destroy_image(game->mlx, game->texture_img[i]);
            game->texture_img[i] = NULL;
        }
        i--;
    }
}

void    free_map(t_data *conf)
{
    int i = 0;

    while(i < conf->map_height)
    {
        free(conf->map[i]);
        i++;
    }
    free(conf->map);
}

void free_sprites(my_game *game)
{
    int i = 0;
    while (i < MAX_SPRITES)
    {
        if (game->sprites[i].img != NULL)
        {
            mlx_destroy_image(game->mlx, game->sprites[i].img);
            game->sprites[i].img = NULL;
        }
        i++; 
    }
}

void	handle_esc(my_game *game)
{

    free_map(game->conf);
    free_textures(game);
    free_sprites(game);
    if (game->z_buffer != NULL)
    {
        free(game->z_buffer);
        game->z_buffer = NULL;
    }
	mlx_destroy_image(game->mlx, game->img->img_ptr);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit (0);
}

void isnot_wall(my_game *game, double x, double y)
{
    if (game->conf->map[(int)y][(int)x] != '\0' && game->conf->map[(int)y][(int)x] != '1')
    {
        game->player_x = x;
        game->player_y = y;
    }
}

void ft_move_y(char c, my_game *game, double ms)
{
    double new_x;
    double new_y;

    if(c == '+')
    {
        new_x = game->player_x + game->player_dir_x * ms;
        new_y = game->player_y + game->player_dir_y * ms;
        isnot_wall(game, new_x, new_y);
    }
    else if (c == '-')
    {
        new_x = game->player_x - game->player_dir_x * ms;
        new_y = game->player_y - game->player_dir_y * ms;
        isnot_wall(game, new_x, new_y);
    }
}

void ft_move_x(char c, my_game *game, double ms)
{
    double new_x;
    double new_y;

    if(c == '<')
    {
        new_x = game->player_x + game->player_dir_y * ms;
        new_y = game->player_y - game->player_dir_x * ms;
        isnot_wall(game, new_x, new_y);
    }
    else if(c == '>')
    {
        double new_x = game->player_x - game->player_dir_y * ms;
        double new_y = game->player_y + game->player_dir_x * ms;
        isnot_wall(game, new_x, new_y);        
    }
}

void ft_move_z(char c, my_game *game, double rs)
{
    double old_dir_x;
    double old_plane_x;

    if (c == ')')
    {
        old_dir_x = game->player_dir_x;
        game->player_dir_x = game->player_dir_x * cos(rs) - game->player_dir_y * sin(rs);
        game->player_dir_y = old_dir_x * sin(rs) + game->player_dir_y * cos(rs);
        old_plane_x = game->plane_x;
        game->plane_x = game->plane_x * cos(rs) - game->plane_y * sin(rs);
        game->plane_y = old_plane_x * sin(rs) + game->plane_y * cos(-rs);
    }
    else if(c == '(')
    {
        old_dir_x = game->player_dir_x;
        game->player_dir_x = game->player_dir_x * cos(-rs) - game->player_dir_y * sin(-rs);
        game->player_dir_y = old_dir_x * sin(-rs) + game->player_dir_y * cos(-rs);

        old_plane_x = game->plane_x;
        game->plane_x = game->plane_x * cos(-rs) - game->plane_y * sin(-rs);
        game->plane_y = old_plane_x * sin(-rs) + game->plane_y * cos(-rs);
    }
}

int handle_keypress(int kc, my_game *game)
{
    double move_speed;
    double rot_speed;

    move_speed = 0.1;
    rot_speed = 0.05;


    if (kc == ESC_KEY)
		handle_esc(game);
    if (kc == W_KEY)
        ft_move_y('+', game, move_speed);
    else if (kc == S_KEY)
        ft_move_y('-', game, move_speed);
    else if (kc == A_KEY)
        ft_move_x('<', game, move_speed);
    else if (kc == D_KEY)
        ft_move_x('>', game, move_speed);
    else if (kc == RIGHT_ARROW)
        ft_move_z(')', game, rot_speed);
    else if (kc == LEFT_ARROW)
        ft_move_z('(', game, rot_speed);
    clear_image(game, game->img);
    render_map(game); // Redraw the scene
    return 0;
}
