/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:39:16 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/31 18:30:58 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ns(t_game *g)
{
	if (g->conf->player == 'S')
	{
		g->player_dir_x = 1;
		g->player_dir_y = 0;
		g->plane_x = -0.66;
		g->plane_y = 0.0;
	}
	else if (g->conf->player == 'N')
	{
		g->player_dir_x = 0;
		g->player_dir_y = -1;
		g->plane_x = 0.66;
		g->plane_y = 0.0;
	}
}

void	ew(t_game *g)
{
	if (g->conf->player == 'E')
	{
		g->player_dir_x = 1;
		g->player_dir_y = 0;
		g->plane_x = 0.0;
		g->plane_y = 0.66;
	}
	else if (g->conf->player == 'W')
	{
		g->player_dir_x = -1;
		g->player_dir_y = 0;
		g->plane_x = 0.0;
		g->plane_y = -0.66;
	}
}

void	ft_player_orientation(t_game *g)
{
	ns(g);
	ew(g);
}
