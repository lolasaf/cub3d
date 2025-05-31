/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flooding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 23:16:01 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/31 23:16:10 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_ing(char **map, t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != '1' && map[y][x] != 'X' && map[y][x] != ' ')
				flood_it(map, x, y, data);
			x++;
		}
		y++;
	}
}

void	flood_it(char **map, int x, int y, t_data *data)
{
	if (x < 0 || y < 0 || map[y] == NULL || map[y][x] == '\0')
	{
		ft_free_map(map);
		err_msg("Map is not properly closed", data->build, (t_data *)data);
	}
	if (map[y][x] == '1' || map[y][x] == 'X')
		return ;
	map[y][x] = 'X';
	flood_it(map, x + 1, y, data);
	flood_it(map, x - 1, y, data);
	flood_it(map, x, y + 1, data);
	flood_it(map, x, y - 1, data);
}
