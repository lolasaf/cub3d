/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:40:29 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/26 09:00:21 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	isnot_wall(my_game *game, double x, double y)
{
	if (game->conf->map[(int)y][(int)x] != '\0'
		&& game->conf->map[(int)y][(int)x] != '1')
	{
		game->player_x = x;
		game->player_y = y;
	}
}

int	handle_keypress(int kc, my_game *game)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.05;
	rot_speed = 0.05;
	if (kc == ESC_KEY)
		exit_game(game);
	if (kc == W_KEY && game->keys->key_up == true)
		ft_move_y('+', game, move_speed);
	if (kc == S_KEY && game->keys->key_down == true)
		ft_move_y('-', game, move_speed);
	if (kc == A_KEY && game->keys->key_left == true)
		ft_move_x('<', game, move_speed);
	if (kc == D_KEY && game->keys->key_right == true)
		ft_move_x('>', game, move_speed);
	if (kc == RIGHT_ARROW && game->keys->rotate_r == true)
		ft_move_z(')', game, rot_speed);
	if (kc == LEFT_ARROW && game->keys->rotate_l == true)
		ft_move_z('(', game, rot_speed);
	clear_image(game, game->img);
	render_game(game);
	return (0);
}

int	mouse_hook(int kc, int x, int y, my_game *game)
{
	double	rot_speed;

	rot_speed = 0.05;
	x = y;
	y = x;
	if (kc == SCROLL_DOWN)
		ft_move_z(')', game, rot_speed);
	else if (kc == SCROLL_UP)
		ft_move_z('(', game, rot_speed);
	clear_image(game, game->img);
	render_game(game);
	return (0);
}

void	ft_mlx_hook_loop(my_game *game)
{
	mlx_hook(game->win, 2, 1, ft_on_press, game);
	mlx_hook(game->win, 3, 2, ft_on_release, game);
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_hook(game->win, 17, 0, exit_game, game);
	mlx_hook(game->win, 4, 1L << 2, mouse_hook, game);
	mlx_loop(game->mlx);
}
