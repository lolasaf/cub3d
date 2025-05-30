/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 00:19:21 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/30 21:41:30 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// W A:97 S:115 D:100 LEFT:65361 Right: 65363
int	ft_on_press(int kc, t_game *g)
{
	if (kc == W_KEY)
		g->keys->key_up = true;
	if (kc == S_KEY)
		g->keys->key_down = true;
	if (kc == A_KEY)
		g->keys->key_left = true;
	if (kc == D_KEY)
		g->keys->key_right = true;
	if (kc == LEFT_ARROW)
		g->keys->rotate_l = true;
	if (kc == RIGHT_ARROW)
		g->keys->rotate_r = true;
	return (0);
}

// W A:97 S:115 D:100 LEFT:65361 Right: 65363
int	ft_on_release(int kc, t_game *g)
{
	if (kc == W_KEY)
		g->keys->key_up = false;
	if (kc == S_KEY)
		g->keys->key_down = false;
	if (kc == A_KEY)
		g->keys->key_left = false;
	if (kc == D_KEY)
		g->keys->key_right = false;
	if (kc == LEFT_ARROW)
		g->keys->rotate_l = false;
	if (kc == RIGHT_ARROW)
		g->keys->rotate_r = false;
	return (0);
}
