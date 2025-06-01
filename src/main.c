/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:18:24 by kforfoli          #+#    #+#             */
/*   Updated: 2025/06/01 22:17:35 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data				data;
	t_game				game;
	t_imgp				img;
	t_press				ks;
	t_texture_object	ob;

	parse(argc, argv, &data);
	if (data.sprites == 1)
		print_menu();
	else
		classic_cube();
	game.img = &img;
	game.conf = &data;
	game.conf->o = &ob;
	game.keys = ft_init_keys(&ks);
	initialize_game(&game, &data);
	render_game(&game);
	ft_mlx_hook_loop(&game);
	exit(EXIT_SUCCESS);
}
