/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:03:57 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/29 22:17:03 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_borders(char **map, t_data *d, int rows, int cols)
{
	if (d->num[0] == 0 || d->num[0] == rows - 1 || d->num[1] == 0
		|| d->num[1] == cols - 1)
	{
		ft_free_map(map);
		err_msg("Player cannot be in borders", d->build, d);
	}
}

int	set_player(char c, int i, int j, t_data *data)
{
	if (!is_valid_char(c))
		err_msg("Error: Invalid character in map", NULL, (t_data *)data);
	if (is_player(c))
	{
		data->player = c;
		data->num[0] = i;
		data->num[1] = j;
		return (1);
	}
	return (0);
}

int	find_player(char **map, int rows, int cols, t_data *data)
{
	int		p_count;
	int		i;
	int		j;
	char	c;

	p_count = 0;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			c = map[i][j];
			if (set_player(c, i, j, data))
				p_count++;
			if (p_count != 0)
				check_borders(map, data, rows, cols);
			j++;
		}
		i++;
	}
	return (p_count);
}
