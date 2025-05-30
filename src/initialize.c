/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:40:20 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/30 21:35:01 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_press	*ft_init_keys(t_press *k)
{
	k->key_up = false;
	k->key_down = false;
	k->key_left = false;
	k->key_right = false;
	k->rotate_l = false;
	k->rotate_r = false;
	return (k);
}

void	initialize_game(t_game *game, t_data *data)
{
	game->z_buffer = (double *)malloc(SCREEN_WIDTH * sizeof(double));
	if (!game->z_buffer)
		err_msg("Failed to allocate z buff", NULL, (t_data *)data);
	game->mlx = mlx_init();
	if (!game->mlx)
		err_msg("Failed to initialize mlx", NULL, (t_data *)data);
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, \
		SCREEN_HEIGHT, "cub3d");
	(game->img)->img_ptr = mlx_new_image(game->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	if (!game->img->img_ptr)
		err_msg("Failed to create main img", NULL, (t_data *)data);
	(game->img)->addr = mlx_get_data_addr(game->img->img_ptr, &game->img->bbp,
			&game->img->line_length, &game->img->endian);
	if (!game->img->addr)
		err_msg("Failed to get address", NULL, (t_data *)data);
	game->player_x = (double)data->num[1] + 0.5;
	game->player_y = (double)data->num[0] + 0.5;
	ft_player_orientation(game);
	mlx_texture_load(game);
	mlx_sprite_load(game);
}
