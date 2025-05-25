/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:56:06 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/25 00:53:48 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_it(char **map, int x, int y)
{
	if (x < 0 || y < 0 || map[y] == NULL || map[y][x] == '\0')
		err_msg("Map is not properly closed");
	if (map[y][x] == '1' || map[y][x] == 'X')
		return ;
	map[y][x] = 'X';
	flood_it(map, x + 1, y);
	flood_it(map, x - 1, y);
	flood_it(map, x, y + 1);
	flood_it(map, x, y - 1);
}

void	pad_map(char **map, char **lines, int rows, int cols)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	while (i < rows) 
	{
		strcpy(map[i], lines[i]);
		len = ft_strlen(lines[i]);
		j = len;
		while (j < cols) 
		{
			map[i][j] = ' ';
			j++;
		}
		i++;
	}
}

char	**init_map(char **lines, int count, t_data *data)
{
	char	**map;
	int		i;

	data->map_height = count;
	data->map_width = get_width(lines, count);
	map = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!map)
		err_msg("Memory allocation error for map rows");
	i = 0;
	while (i < data->map_height) 
	{
		map[i] = ft_calloc(data->map_width + 1, sizeof(char));
		if (!map[i])
		{
			ft_free_map(map);
			err_msg("Memory allocation error for map row content");
		}
		i++;
	}
	map[data->map_height] = NULL;
	return (map);
}

char	**pvmap(char **lines, int count, t_data *data)
{
	char	**map;
	int		p_count;

	if (!lines || count <= 0)
		err_msg("Invalid input to pvmap: \
			lines are NULL or count is non-positive");
	map = init_map(lines, count, data);
	pad_map(map, lines, data->map_height, data->map_width);
	p_count = find_player(map, data->map_height, data->map_width, data);
	if (p_count != 1)
		err_msg("Error: Map must contain exactly one player position");
	flood_it(map, data->num[1], data->num[0]);
	return (map);
}

void	process_map(t_build *b, t_data *data)
{
	char	**valid;

	valid = pvmap(b->map_lines, b->count, data);
	data->map = valid;
}
