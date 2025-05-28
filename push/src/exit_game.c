/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:41:42 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/27 18:53:32 by kforfoli         ###   ########.fr       */
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

void	free_textures(my_game *game)
{
	int	i;

	i = 3;
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

void	free_map(t_data *conf)
{
	int	i;

	i = 0;
	while (i < conf->map_height)
	{
		free(conf->map[i]);
		i++;
	}
	free(conf->map);
}

void free_build(t_build *build)
{
	if (build)
	{
		int i = 0;
		while(i < build->count)
		{
			free(build->map_lines[i]);
			build->map_lines[i] = NULL;
			i++;
		}
	}
}

void free_map_v2(t_data *conf)
{
	int i = 0;
	if (!conf)
		return;
	if (conf->map) //maybe use map_height or null terminate final conf->map[i]
	{
		while (conf->map[i] != NULL)
		{
			free(conf->map[i]);
			conf->map[i] = NULL;
			i++;
		}
		free(conf->map);
	}
	i = 0;
	if (conf->texture[i].identifier)
	{
		while(i < 4 && conf->texture[i].identifier)
		{
			free(conf->texture[i].identifier);
			conf->texture[i].identifier = NULL;
			if (conf->texture[i].path)	
				free(conf->texture[i].path);
			conf->texture[i].path = NULL;
			i++;
		}
	}
}

void	free_sprites(my_game *game)
{
	int	i;

	i = 0;
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

int	exit_game(my_game *game)
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
	exit(0);
}
