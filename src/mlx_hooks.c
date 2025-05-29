/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:17:51 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/30 01:19:29 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_hook_loop(t_game *game)
{
	mlx_hook(game->win, 2, 1, ft_on_press, game);
	mlx_hook(game->win, 3, 2, ft_on_release, game);
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_hook(game->win, 17, 0, exit_game, game);
	mlx_hook(game->win, 4, 1L << 2, mouse_hook, game);
	mlx_loop(game->mlx);
}
