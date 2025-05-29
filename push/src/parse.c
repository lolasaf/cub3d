/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:21:01 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/29 20:16:10 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void dual(int *fd, t_build *assmbl, t_data *data, char *msg)
{
	close(*fd);
	err_msg(msg, assmbl, data);
}

char	*add_map_line(t_build *assmbl, const char *line, t_data *data, int *fd)
{
	char	*cpy;
	char	*next;
	int		distance;

	cpy = (char *)line;
	next = get_next_line(*fd);
	if (assmbl->count >= MAX_LINES)
	{
		free_block(next);
		dual(fd, assmbl, data, "Too many lines");
	}
	if (ft_strchr(cpy, '\n') != NULL)
	{
		distance = ft_strchr(cpy, '\n') - cpy;
		cpy[distance] = '\0';
	}
	assmbl->map_lines[assmbl->count] = ft_strdup(cpy);
	free_block(cpy);
	if (!assmbl->map_lines[assmbl->count])
		dual(fd, assmbl, data, "ft_strdup failed");
	assmbl->count++;
	if (next == NULL || *next == '\n')
		data->is_last++;
	return (next);
}

char	*newline(char *line, t_data *d, int *fd)
{
	if (*line != '\n')
	{
		ft_parse_tandc(line, d);
		free_block(line);
		line = get_next_line(*fd);
	}
	else
	{
		free_block(line);
		line = get_next_line(*fd);
	}
	return (line);
}

char	*check_map(char *is_line, int *fd, int *stop)
{
	char    *trimmed;                                       
    char *another;                             
	trimmed = NULL;        
	another = is_line;                                                                                    
	trimmed = ft_trim(is_line);                     
	while (trimmed != NULL && *trimmed == '\n')
	{
		free_block(another);
		another = get_next_line(*fd);     
		trimmed = ft_trim(another);  
	}
	if (trimmed != NULL)                            
	{
		free_block(another);                          
		trimmed = ft_strdup("freebuilt");       
		return trimmed;                         
	}
	else                                            
	{
		*stop = 1;
		return NULL;                              
	}
	char *ret = ft_strdup(trimmed);
	free_block(another);
	free_block(is_line);
	return (ret);                                   

}

void	parse_func(char *file, t_build *b, t_data *data)
{

	int		fd = 0;
	char	*line = NULL;
	char	*is_line = NULL;
	int		stop = 0;
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
						break;
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
}


void	parse(int argc, char **argv, t_data *data)
{
	t_build	b;

	memset(data, 0, sizeof(t_data));
	if (argc != 2)
		err_msg("Only two args allowed!", NULL, NULL);
	memset(&b, 0, sizeof(t_build));
	b.count = 0;
	data->is_last = 0;
	data->build = &b;
	ft_ext_check(argv[1], ".cub");
	parse_func(argv[1], &b, data);
	if (b.map_lines[0] == NULL)
		err_msg("Map parsing error!", (t_build *)&b, (t_data *)data);
	ft_validate_textures(data);
	process_map(&b, data);
	free_build(&b);
	data->build = NULL;
}
