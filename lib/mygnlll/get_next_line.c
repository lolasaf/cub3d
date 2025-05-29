/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:49:06 by kforfoli          #+#    #+#             */
/*   Updated: 2024/02/14 20:26:40 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*buf(int fd, char *left_c, char *buffer);
static char	*remain_der(char *rem);

static char	*buf(int fd, char *left_c, char *buffer)
{
	ssize_t	read_buf;
	char	*hold_left_c;

	read_buf = 1;
	while (read_buf > 0)
	{
		read_buf = read(fd, buffer, BUFFER_SIZE);
		if (read_buf == -1)
		{
			free(left_c);
			return (NULL);
		}
		else if (read_buf == 0)
			break ;
		buffer[read_buf] = 0;
		if (!left_c)
			left_c = ft_strdup("");
		hold_left_c = left_c;
		left_c = ft_strjoin(hold_left_c, buffer);
		free(hold_left_c);
		hold_left_c = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left_c);
}

static char	*remain_der(char *rem)
{
	char	*left_c;
	size_t	i;

	i = 0;
	while (rem[i] != '\n' && rem[i] != '\0')
		i++;
	if (rem[i] == 0 || rem[1] == 0)
		return (NULL);
	left_c = ft_substr(rem, i + 1, ft_strlen(rem) - i);
	if (*left_c == 0)
	{
		free(left_c);
		left_c = NULL;
	}
	rem[i + 1] = 0;
	return (left_c);
}

char	*get_next_line(int fd)
{
	static char	*left_c[4096];
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(left_c[fd]);
		free(buffer);
		left_c[fd] = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = buf(fd, left_c[fd], buffer);
	free (buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	left_c[fd] = remain_der(line);
	return (line);
}
/*
int	main(void)
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file.\n");
		return (1);
	}
	while(get_next_line(fd)!= NULL)
	{
		line = get_next_line(fd);
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/
