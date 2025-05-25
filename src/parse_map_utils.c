/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3parse_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:02:47 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/24 23:10:34 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_map(char **map)
{
	int	i;

	if (map == NULL) 
		return ;
	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]); 
		map[i] = NULL; 
		i++;
	}
	free(map); 
	map = NULL;
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || is_player(c) || c == ' ');
}

int	get_width(char **m_lines, int count)
{
	int	max;
	int	i;
	int	len;

	i = 0;
	max = 0;
	while (i < count)
	{
		len = ft_strlen(m_lines[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}
