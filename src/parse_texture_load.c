/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_load.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:15:24 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/24 23:15:50 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture_img(my_game *game)
{
	game->texture_img[0] = \
		mlx_xpm_file_to_image(game->mlx, game->conf->texture[0].path,
			&game->conf->o->width, &game->conf->o->height);
	game->texture_img[1] = \
		mlx_xpm_file_to_image(game->mlx, game->conf->texture[1].path,
			&game->conf->o->width, &game->conf->o->height);
	game->texture_img[2] = \
		mlx_xpm_file_to_image(game->mlx, game->conf->texture[2].path,
			&game->conf->o->width, &game->conf->o->height);
	game->texture_img[3] = \
		mlx_xpm_file_to_image(game->mlx, game->conf->texture[3].path,
			&game->conf->o->width, &game->conf->o->height);
	game->texture_img[4] = NULL;
	if (!game->texture_img[0] || !game->texture_img[1] || !game->texture_img[2]
		|| !game->texture_img[3])
		err_msg("Failed to load textures");
}

void	set_dets(my_game *game)
{
	game->conf->o->texture_addr[0] = (unsigned int *)mlx_get_data_addr(
			game->texture_img[0], &game->conf->o->texture_bpp[0],
			&game->conf->o->texture_ll[0], &game->conf->o->texture_endian[0]);
	game->conf->o->texture_addr[1] = (unsigned int *)mlx_get_data_addr(
			game->texture_img[1], &game->conf->o->texture_bpp[1],
			&game->conf->o->texture_ll[1], &game->conf->o->texture_endian[1]);
	game->conf->o->texture_addr[2] = (unsigned int *)mlx_get_data_addr(
			game->texture_img[2], &game->conf->o->texture_bpp[2],
			&game->conf->o->texture_ll[2], &game->conf->o->texture_endian[2]);
	game->conf->o->texture_addr[3] = (unsigned int *)mlx_get_data_addr(
			game->texture_img[3], &game->conf->o->texture_bpp[3],
			&game->conf->o->texture_ll[3], &game->conf->o->texture_endian[3]);
	if (!game->conf->o->texture_addr[0] || !game->conf->o->texture_addr[1]
		|| !game->conf->o->texture_addr[2] || !game->conf->o->texture_addr[3])
		err_msg("Failed to get texture address");
}

void	mlx_texture_load(my_game *game)
{
	load_texture_img(game);
	set_dets(game);
}
