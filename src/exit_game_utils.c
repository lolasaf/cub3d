/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:50:17 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/30 20:19:28 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_block(void *block)
{
	if (block)
		free(block);
	block = NULL;
}

void	destroy_mlx(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img->img_ptr);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	destroy_buffer(t_game *game)
{
	if (game->z_buffer != NULL)
	{
		free(game->z_buffer);
		game->z_buffer = NULL;
	}
}

void	free_texture_vars(t_data *conf)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free_block(conf->texture[i].path);
		free_block(conf->texture[i].identifier);
		i++;
	}
}

void	free_textures(t_game *game)
{
	int	i;

	i = 3;
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
