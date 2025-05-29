/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_tok.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:35:57 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/29 23:15:14 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_floor(t_data *data, int values[3])
{
	data->color[0].type = 'F';
	data->color[0].rgb[0] = values[0];
	data->color[0].rgb[1] = values[1];
	data->color[0].rgb[2] = values[2];
	return (1);
}

int	set_ceiling(t_data *data, int values[3])
{
	data->color[1].type = 'C';
	data->color[1].rgb[0] = values[0];
	data->color[1].rgb[1] = values[1];
	data->color[1].rgb[2] = values[2];
	return (2);
}

void	parse_color_tok(char id, char *token, t_data *data, char *frline)
{
	static int	j;
	int			i;
	int			values[3];

	// values[0] = 0;
	// values[1] = 0;
	// values[2] = 0;
	ft_memset(values, 0, 3);
	token = trim(token);
	if (!parse_color(token, values))
	{
		free_block(frline);
		err_msg("Failed to parse color values!", NULL, (t_data *)data);
	}
	i = 0;
	while (i < 3)
	{
		if (values[i] < 0 || values[i] > 255)
		{
			free_block(frline);
			err_msg("Color values out of range", NULL, (t_data *)data);
		}
		i++;
	}
	if (id == 'F')
		j += set_floor(data, values);
	else if (id == 'C')
		j += set_ceiling(data, values);
	if (j == 3)
		data->is_last++;
}
