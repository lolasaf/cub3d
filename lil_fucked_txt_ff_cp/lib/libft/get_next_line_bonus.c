/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:58:39 by wel-safa          #+#    #+#             */
/*   Updated: 2023/08/09 20:12:54 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*newread;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	newread = (char *)ft_calloc(1, BUFFER_SIZE + 1);
	if (!newread)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = (char *)ft_calloc(1, 1);
		if (!buffer[fd])
		{
			free(newread);
			return (NULL);
		}
	}
	buffer[fd] = get_next_line_2(fd, buffer[fd], newread);
	if (!buffer[fd])
		return (NULL);
	return (ft_splitnl(buffer[fd], ft_checknl(buffer[fd])));
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

char	*ft_free_null(char *buffer, char *newread)
{
	free(buffer);
	free(newread);
	return (NULL);
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