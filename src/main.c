/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:18:24 by kforfoli          #+#    #+#             */
/*   Updated: 2025/06/02 19:18:52 by kforfoli         ###   ########.fr       */
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
	// ft_mlx_hook_loop(&game);
	mlx_hook(game.win, 4, 1L << 2, mouse_hook_2, &game);
	mlx_hook(game.win, 3, 2, ft_on_release, &game);
	mlx_hook(game.win, 2, 1, ft_on_press, &game);
	mlx_hook(game.win, 17, 0, exit_game, &game);
	// mlx_hook(game.win, 6, 1L << 6, mouse_hook_2, &game);
	// mlx_hook(game.win, 4, 1L << 2, mouse_hook, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	exit(EXIT_SUCCESS);
}
