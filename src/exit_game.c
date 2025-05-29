/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:41:42 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/30 00:07:35 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_data *conf)
{
	int	i;

	i = 0;
	if (!conf)
		return ;
	if (!conf->map)
		return ;
	while (i < conf->map_height)
	{
		free_block(conf->map[i]);
		i++;
	}
	free_block(conf->map);
}

void	free_build(t_build *build)
{
	int	i;

	i = 0;
	if (build)
	{
		while (i < build->count)
		{
			free_block(build->map_lines[i]);
			i++;
		}
	}
}

void	free_sprites(my_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_sprites)
	{
		if (game->sprites[i].img != NULL)
		{
			mlx_destroy_image(game->mlx, game->sprites[i].img);
			game->sprites[i].img = NULL;
		}
		i++;
	}
}

int	exit_game(my_game *game)
{
	free_map(game->conf);
	free_textures(game);
	free_sprites(game);
	destroy_buffer(game);
	destroy_mlx(game);
	exit(0);
}
