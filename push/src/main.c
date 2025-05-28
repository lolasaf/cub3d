/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:18:24 by kforfoli          #+#    #+#             */
/*   Updated: 2025/05/25 02:24:02 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data				data;
	my_game				game;
	t_imgp				img;
	t_press				ks;
	t_texture_object	ob;

	parse(argc, argv, &data);
	game.img = &img;
	game.conf = &data;
	game.conf->o = &ob;
	game.keys = ft_init_keys(&ks);
	initialize_game(&game, &data);
	render_game(&game);
	ft_mlx_hook_loop(&game);
	exit(EXIT_SUCCESS);
}
