/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:11:00 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/29 13:51:41 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_texture(t_data *data, int i, char *path, char *str)
{
	int		j;
	char	*nl;

	j = 1;
	nl = ft_strchr(path, '\n');
	if (nl)
		*nl = '\0';
	data->texture[i].identifier = ft_strdup(str);
	data->texture[i].path = ft_strdup(path);
	j = j + i;
	return (j);
}

int	ft_parse_texture(char *token, char *line, t_data *data, char *frline)
{
	char		*trimmed;
	static int	i;

	trimmed = trim(line);
	if (i == 10)
	{
		free(token);
		token = NULL;
		free(frline);
		frline = NULL;
		err_msg("Duplicate texture detected", NULL, (t_data *)data);
	}
	if (ft_strncmp(token, "NO", 2) == 0)
		i += set_texture(data, 0, trimmed, "NO");
	if (ft_strncmp(token, "SO", 2) == 0)
		i += set_texture(data, 1, trimmed, "SO");
	if (ft_strncmp(token, "WE", 2) == 0)
		i += set_texture(data, 2, trimmed, "WE");
	if (ft_strncmp(token, "EA", 2) == 0)
		i += set_texture(data, 3, trimmed, "EA");
	if (i == 10)
		data->is_last++;
	return (1);
}

void	ft_check_xpm(char *path, const char *xpm, t_data *data)
{
	const char	*base;
	const char	*slash;
	const char	*dot;

	slash = ft_strrchr(path, '/');
	if (slash != NULL)
		base = slash + 1;
	else
		base = path;
	dot = ft_strrchr(base, '.');
	if (dot == NULL)
		err_msg("ERR:Not a valid texture", NULL, (t_data *)data);
	if (strcmp(dot, xpm) != 0)
		err_msg("ERR: Not a valid texture", NULL, (t_data *)data);
}

void	ft_validate_textures(t_data *data)
{
	int	i;

	if (data->texture[0].path == NULL || data->texture[1].path == NULL
		|| data->texture[2].path == NULL || data->texture[3].path == NULL)
		err_msg("Texture paths not provided", NULL, (t_data *)data);
	i = 0;
	while (i < 4)
	{
		ft_check_xpm(data->texture[i].path, ".xpm", data);
		i++;
	}
}
