/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:02:01 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/29 23:02:40 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
if 1 -> break
if 2-> err_msg("New line detected in map", b, data)
if 0 -> do nothing*/
int	checker(char **line, char **is_line, int fd, int *stop)
{
	*is_line = check_map(*is_line, &fd, stop);
	if (*stop == 1)
	{
		if (*is_line)
		{
			free_block(*is_line);
			free_block(*line);
			return (1);
		}
	}
	if (*is_line && ft_strncmp(*is_line, "freebuilt", 10) == 0)
	{
		free_block(*is_line);
		close(fd);
		return (2);
	}
	return (0);
}

void	init_parse_func(char **line, char **is_line, int fd, int *stop)
{
	*line = NULL;
	*is_line = NULL;
	*stop = 0;
	*line = get_next_line(fd);
}

void	parse_func(int fd, t_build *b, t_data *data)
{
	char	*line;
	char	*is_line;
	int		stop;
	int		j;

	init_parse_func(&line, &is_line, fd, &stop);
	while (line != NULL && stop == 0)
	{
		if (data->is_last == 2 && *line != '\n')
		{
			is_line = add_map_line(b, line, data, &fd);
			if (data->is_last == 3)
			{
				j = checker(&line, &is_line, fd, &stop);
				if (j == 1)
					break ;
				if (j == 2)
					err_msg("New line detected in map", b, data);
			}
			line = is_line;
		}
		else
			line = newline(line, data, &fd);
	}
	close(fd);
}

/*void	parse_func(char *file, t_build *b, t_data *data)
{
	int		fd;
	char	*line;
	char	*is_line;
	int		stop;

	line = NULL;
	is_line = NULL;
	stop = 0;
	fd = open(file, O_RDONLY);
	if (fd < 1)
		err_msg("Failed to open file", NULL, NULL);
	line = get_next_line(fd);
	while (line != NULL && stop == 0)
	{
		if (data->is_last == 2 && *line != '\n')
		{
			is_line = add_map_line(b, line, data, &fd);
			if (data->is_last == 3)
			{
				is_line = check_map(is_line, &fd, &stop);
				if (stop == 1)
				{
					if (is_line)
					{
						free_block(is_line);
						free_block(line);
						break ;
					}
				}
				if (is_line && ft_strncmp(is_line, "freebuilt", 10) == 0)
				{
					free_block(is_line);
					close(fd);
					err_msg("New line detected in map", b, data);
				}
			}
			line = is_line;
		}
		else
			line = newline(line, data, &fd);
	}
	close(fd);
}*/
