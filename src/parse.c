/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:21:01 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/25 02:19:15 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*add_map_line(t_build *assmbl, const char *line, t_data *data, int *fd)
{
	char	*cpy;
	char	*next;
	int		distance;

	cpy = (char *)line;
	next = get_next_line(*fd);
	if (assmbl->count >= MAX_LINES)
	{
		free(next);
		err_msg("Too many lines"); // check exit
	}
	if (ft_strchr(cpy, '\n') != NULL)
	{
		distance = ft_strchr(cpy, '\n') - cpy;
		cpy[distance] = '\0';
	}
	assmbl->map_lines[assmbl->count] = ft_strdup(cpy);
	free(cpy);
	if (!assmbl->map_lines[assmbl->count])
		err_msg("ft_strdup failed"); // check exit
	assmbl->count++;
	if (next == NULL || *next == '\n')
		data->is_last++;
	return (next);
}

void	parse_func(char *file, t_build *b, t_data *data)
{
	int		fd;
	char	*line;
	char	*is_line;
	char	*trimmed;

	fd = open(file, O_RDONLY);
	if (fd < 1)
		err_msg("Failed to open file");
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (data->is_last == 2 && *line != '\n')
		{
			is_line = add_map_line(b, line, data, &fd);
			if (data->is_last == 3)
			{
				trimmed = ft_trim(is_line);
				while (trimmed != NULL && *trimmed == '\n')
				{
					//free(trimmed); // ???? Added this -- not sure
					trimmed = ft_trim(get_next_line(fd));
				}
				if (trimmed != NULL)
					err_msg("New line detected in map");
				else
				{
					free(is_line);
					break ;
				}
			}
			line = is_line;
		}
		else if (*line != '\n')
		{
			ft_parse_tandc(line, data);
			if (line)
				free(line);
			line = get_next_line(fd);
		}
		else
		{
			if (line)
				free(line);
			line = get_next_line(fd);
		}
	}
	close(fd);
}

void	parse(int argc, char **argv, t_data *data)
{
	t_build	b;
	int		j;

	memset(data, 0, sizeof(t_data));
	if (argc != 2)
		err_msg("only two args");
	memset(&b, 0, sizeof(t_build));
	b.count = 0;
	data->is_last = 0;
	ft_ext_check(argv[1], ".cub");
	parse_func(argv[1], &b, data);
	if (b.map_lines[0] == NULL)
		err_msg("Error"); // check exit and free
	ft_validate_textures(data);
	process_map(&b, data);
	j = 0;
	while (j < b.count && b.map_lines[j] != NULL)
		free(b.map_lines[j++]);
}
