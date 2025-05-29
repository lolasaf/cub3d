/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:58:39 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/30 00:49:26 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*g_buffer;

/*
	Check if buffer has new line and return index of line
*/
int	ft_checknl(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (-1);
	if (ft_strlen(buffer) == 0)
		return (-1);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	free_gnl_buffer(void)
{
	if (g_buffer)
		free(g_buffer);
	g_buffer = NULL;
}

/*
	returns string before new line ending in new line and null
	rearranges buffer to keep everything after new line and 
	nulls the rest of the buffer space.
*/
char	*ft_splitnl(char *buff, int i)
{
	int		j;
	char	*temp;

	if (!buff || ft_strlen(buff) == 0)
		return (NULL);
	if (i < 0)
		i = ft_strlen(buff) - 1;
	temp = (char *)ft_calloc(sizeof(char), i + 2);
	if (!temp)
		return (NULL);
	j = -1;
	while (++j <= i)
		temp[j] = buff[j];
	j = -1;
	while (buff[++j])
	{
		if (j < ((int)ft_strlen(buff) - i - 1))
			buff[j] = buff[j + i + 1];
		else
			buff[j] = '\0';
	}
	return (temp);
}

/*char	*get_next_line_save(int fd)
{
	static char	*buffer;
	char		*newread;
	int			bytesread;

	bytesread = 0;
	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	newread = (char *)ft_calloc(1, BUFFER_SIZE + 1);
	if (!newread)
		return (NULL);
	if (!buffer)
	{
		buffer = (char *)ft_calloc(1, 1);
		if (!buffer)
		{
			free(newread);
			return (NULL);
		}
	}
	while (ft_checknl(buffer) < 0)
	{
		bytesread = read(fd, newread, BUFFER_SIZE);
		if (bytesread < 0)
		{
			free(buffer);
			buffer = NULL;
			free(newread);
			return (NULL);
		}
		else if (bytesread == 0)
		{
			if (ft_strlen(buffer) == 0)
			{
				free(buffer);
				buffer = NULL;
				free(newread);
				return (NULL);
			}
			free(newread);
			return (ft_splitnl(buffer, ft_checknl(buffer)));
		}
		newread[bytesread] = 0;
		buffer = ft_buffjoin(buffer, newread);
		if (ft_strlen(buffer) == 0)
		{
			free(buffer);
			free(newread);
			buffer = NULL;
			return (NULL);
		}
	}
	free(newread);
	return (ft_splitnl(buffer, ft_checknl(buffer)));
}*/

char	*get_next_line(int fd)
{
	char		*newread;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	newread = (char *)ft_calloc(1, BUFFER_SIZE + 1);
	if (!newread)
		return (NULL);
	if (!g_buffer)
	{
		g_buffer = (char *)ft_calloc(1, 1);
		if (!g_buffer)
		{
			free(newread);
			return (NULL);
		}
	}
	g_buffer = get_next_line_2(fd, g_buffer, newread);
	if (!g_buffer)
		return (NULL);
	return (ft_splitnl(g_buffer, ft_checknl(g_buffer)));
}

char	*get_next_line_2(int fd, char *buffer, char *newread)
{
	int	bytesread;

	bytesread = 0;
	while (ft_checknl(buffer) < 0)
	{
		bytesread = read(fd, newread, BUFFER_SIZE);
		if (bytesread < 0)
			return (ft_free_null(buffer, newread));
		else if (bytesread == 0)
		{
			if (ft_strlen(buffer) == 0)
				return (ft_free_null(buffer, newread));
			free(newread);
			return (buffer);
		}
		newread[bytesread] = 0;
		buffer = ft_buffjoin(buffer, newread);
		if (ft_strlen(buffer) == 0)
			return (ft_free_null(buffer, newread));
	}
	free(newread);
	return (buffer);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*filepath;
// 	char	*line;
// 	filepath = "empty.txt";
// 	fd = open(filepath, O_RDONLY);
// 	//fd = 0;
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free (line);
// 		line = get_next_line(fd);
// 	}
// 	//line = get_next_line(fd);
// 	if (line)
// 		free (line);
// 	close (fd);
// 	return (0);
// }