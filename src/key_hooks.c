/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:40:29 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/31 18:13:21 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	isnot_wall(t_game *game, double x, double y)
{
	if (game->conf->map[(int)y][(int)x] != '\0'
		&& game->conf->map[(int)y][(int)x] != '1')
	{
		game->player_x = x;
		game->player_y = y;
	}
}

void	kill_sprite(t_game *game, int id)
{
	if (game->sprites[id].img != NULL)
	{
		print_poki(game);
		mlx_destroy_image(game->mlx, game->sprites[id].img);
		game->sprites[id].img = NULL;
	}
}

void	ft_destroy_sprite(t_game *game)
{
	static int	counter = 0;
	int			i;

	i = 0;
	while (i < game->num_sprites)
	{
		if (fabs(game->player_x - game->sprites[i].x) < 0.5
			&& fabs(game->player_y - game->sprites[i].y) < 0.5)
		{
			kill_sprite(game, i);
			counter++;
		}
		i++;
	}
	if (counter == game->num_sprites)
	{
		print_done();
		exit_game(game);
	}
}

// int handle_keypress(int kc, t_game *game)
// {
// 	if (kc == ESC_KEY)
// 		exit_game(game);
// 	if (kc == 32)
// 		ft_destroy_sprite(game);
// 	return (0);
// }

// int	handle_keypress(int kc, t_game *game)
// {
// 	double	move_speed;
// 	double	rot_speed;

// 	move_speed = 0.05;
// 	rot_speed = 0.05;
// 	if (kc == ESC_KEY)
// 		exit_game(game);
// 	if (kc == W_KEY && game->keys->key_up == true)
// 		ft_move_y('+', game, move_speed);
// 	if (kc == S_KEY && game->keys->key_down == true)
// 		ft_move_y('-', game, move_speed);
// 	if (kc == A_KEY && game->keys->key_left == true)
// 		ft_move_x('<', game, move_speed);
// 	if (kc == D_KEY && game->keys->key_right == true)
// 		ft_move_x('>', game, move_speed);
// 	if (kc == RIGHT_ARROW && game->keys->rotate_r == true)
// 		ft_move_z(')', game, rot_speed);
// 	if (kc == LEFT_ARROW && game->keys->rotate_l == true)
// 		ft_move_z('(', game, rot_speed);
// 	if (kc == 32)
// 		ft_destroy_sprite(game);
// 	clear_image(game);
// 	render_game(game);
// 	return (0);
// }

int	mouse_hook(int kc, int x, int y, t_game *game)
{
	double	rot_speed;

	rot_speed = 0.05;
	x = y;
	y = x;
	if (kc == SCROLL_DOWN)
		ft_move_z(')', game, rot_speed);
	else if (kc == SCROLL_UP)
		ft_move_z('(', game, rot_speed);
	clear_image(game);
	render_game(game);
	return (0);
}
