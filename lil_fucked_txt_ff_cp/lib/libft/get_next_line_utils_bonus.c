/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:36:48 by wel-safa          #+#    #+#             */
/*   Updated: 2023/08/09 20:07:17 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	if (!s)
		return (0);
	while (s[n])
		n++;
	return (n);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	bytes;
	void	*ptr;

	bytes = size * nmemb;
	if (size != 0 && nmemb != 0 && bytes / size != nmemb)
		return (NULL);
	ptr = malloc (bytes);
	if (ptr == 0)
		return (0);
	ft_bzero(ptr, bytes);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

/* ft_buffjoin takes the current buffer and the new read temp buff.
It joins both strings into a new malloced buffer, and frees old buffer.
*/
char	*ft_buffjoin(char *buffer, char const *newread)
{
	char	*temp;
	int		i;

	temp = ft_strdup(buffer);
	free(buffer);
	buffer = (char *)ft_calloc(1, ft_strlen(temp) + ft_strlen(newread) + 1);
	if (!buffer)
		return (NULL);
	i = -1;
	while (temp[++i])
		buffer[i] = temp[i];
	while (*newread)
	{
		buffer[i] = *newread;
		newread++;
		i++;
	}
	buffer[i] = 0;
	free(temp);
	return (buffer);
}

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*ptr;
	size_t	i;

	i = 0;
	size = ft_strlen(s);
	ptr = (char *)ft_calloc(1, size + 1);
	if (!ptr)
		return (0);
	while (i < size + 1)
	{
		((char *)ptr)[i] = ((char *)s)[i];
		i++;
	}
	return (ptr);
}
