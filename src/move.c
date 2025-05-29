/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 00:16:24 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/30 01:07:34 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move_x(char c, t_game *game, double ms)
{
	double	new_x;
	double	new_y;

	if (c == '<')
	{
		new_x = game->player_x + game->player_dir_y * ms;
		new_y = game->player_y - game->player_dir_x * ms;
		isnot_wall(game, new_x, new_y);
	}
	else if (c == '>')
	{
		new_x = game->player_x - game->player_dir_y * ms;
		new_y = game->player_y + game->player_dir_x * ms;
		isnot_wall(game, new_x, new_y);
	}
}

void	ft_move_z(char c, t_game *game, double rs)
{
	double	old_dir_x;
	double	old_plane_x;

	if (c == ')')
	{
		old_dir_x = game->player_dir_x;
		game->player_dir_x = game->player_dir_x * cos(rs) - game->player_dir_y
			* sin(rs);
		game->player_dir_y = old_dir_x * sin(rs) + game->player_dir_y * cos(rs);
		old_plane_x = game->plane_x;
		game->plane_x = game->plane_x * cos(rs) - game->plane_y * sin(rs);
		game->plane_y = old_plane_x * sin(rs) + game->plane_y * cos(-rs);
	}
	else if (c == '(')
	{
		old_dir_x = game->player_dir_x;
		game->player_dir_x = game->player_dir_x * cos(-rs) - game->player_dir_y
			* sin(-rs);
		game->player_dir_y = old_dir_x * sin(-rs) + game->player_dir_y
			* cos(-rs);
		old_plane_x = game->plane_x;
		game->plane_x = game->plane_x * cos(-rs) - game->plane_y * sin(-rs);
		game->plane_y = old_plane_x * sin(-rs) + game->plane_y * cos(-rs);
	}
}

void	ft_move_y(char c, t_game *game, double ms)
{
	double	new_x;
	double	new_y;

	if (c == '+')
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
