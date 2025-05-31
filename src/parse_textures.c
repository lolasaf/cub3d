/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:11:00 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/31 18:38:54 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cleanup(char *str)
{
	char	*str2;
	int		i;
	int		c;

	str2 = ft_strdup(str);
	i = 0;
	while (str2[i] && !ft_isspace(str2[i]))
		i++;
	if (!str2[i])
	{
		free(str2);
		return (125);
	}
	c = ft_isspace(str2[i]);
	free(str2);
	return (c);
}

int	set_texture(t_data *data, int i, char *path, char *str)
{
	int		j;
	char	*nl;
	int		c;

	j = 1;
	nl = ft_strchr(path, '\n');
	if (nl)
		*nl = '\0';
	c = cleanup(str);
	if (c != 125)
		ft_trim(str);
	c = cleanup(path);
	if (c != 125)
		ft_trim(path);
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
		free_block(token);
		free_block(frline);
		free_gnl_buffer();
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
		err_msg("Not a valid texture", data->build, data);
	if (ft_strncmp(dot, xpm, 4) != 0)
		err_msg("Not a valid texture", data->build, data);
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
