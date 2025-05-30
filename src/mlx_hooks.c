/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:17:51 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/31 01:00:11 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_keys(t_game *game)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.05;
	rot_speed = 0.03;
	if (game->keys->key_up)
		ft_move_y('+', game, move_speed);
	if (game->keys->key_down)
		ft_move_y('-', game, move_speed);
	if (game->keys->key_left)
		ft_move_x('<', game, move_speed);
	if (game->keys->key_right)
		ft_move_x('>', game, move_speed);
	if (game->keys->rotate_l)
		ft_move_z('(', game, rot_speed);
	if (game->keys->rotate_r)
		ft_move_z(')', game, rot_speed);
}

int game_loop(t_game *game)
{
	update_keys(game);
	clear_image(game);
	render_game(game);
	return (0);
}

void	ft_mlx_hook_loop(t_game *game)
{
	mlx_hook(game->win, 3, 2, ft_on_release, game);
	mlx_hook(game->win, 2, 1, ft_on_press, game);
	//mlx_key_hook(game->win, handle_keypress, game);
	mlx_hook(game->win, 17, 0, exit_game, game);
	mlx_hook(game->win, 4, 1L << 2, mouse_hook, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}
