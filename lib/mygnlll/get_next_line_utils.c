/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:51:24 by kforfoli          #+#    #+#             */
/*   Updated: 2024/02/13 19:16:28 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
// int main(void)
// {
// 	const char *s = "Hello";
// 	size_t i = (size_t)strlen(s);
// 	size_t j = ft_strlen(s);
// 	printf("ORIGINAL: %zu\n", i);
// 	printf("MINE: %zu\n", j);
// 	return (0);
// }

/*
char	*ft_strchr(const char *s, int d)
{
	unsigned int	i;
	char			c;
	char			*s_cpy;

	i = 0;
	c = (char)d;
	s_cpy = (char *)s;
	while (s_cpy[i])
	{
		if (s_cpy[i] != c)
			i++;
		break ;
	}
	return (&s_cpy[i]);
}
*/
char	*ft_strchr(const char *s, int d)
{
	unsigned int	i;
	char			c;
	char			*s_cpy;

	i = 0;
	c = (char)d;
	s_cpy = (char *)s;
	while (s_cpy[i])
	{
		if (s_cpy[i] == c)
			return (&s_cpy[i]);
		i++;
	}
	if (s_cpy[i] == c)
		return (&s_cpy[i]);
	return (NULL);
}
// int	main(void)
// {
// 	const char *string = "Hello ehm esma essen";
// 	unsigned int i = 101;
// 	char *mine = ft_strchr(string,i);
// 	char *original = strchr(string, i);
// 	printf("MINE: %p\n", mine);
// 	printf ("OG: %p\n", original);
// 	return 0;

// }
char	*ft_strdup(const char *s)
{
	unsigned int	i;
	char			*s_dup;

	i = 0;
	s_dup = (char *)malloc((ft_strlen(s) + 1) * sizeof(const char));
	if (!s_dup)
		return (NULL);
	while (s[i])
	{
		s_dup[i] = s[i];
		i++;
	}
	s_dup[i] = '\0';
	i = 0;
	return (&s_dup[i]);
}

// int	main(void)
// {
// 	const char *s = "Helloooo ";
// 	//char *orig = ft_strdup(s);
// 	printf("STRING: %s\n", ft_strdup(s));
// 	return 0;

// }

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*substring;

	i = 0;
	if (!s || start >= ft_strlen(s))
	{
		substring = (char *)malloc(1);
		if (!substring)
			return (NULL);
		substring[0] = '\0';
		return (substring);
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substring = (char *)malloc((len + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	while (i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
/*
int	main(void)
{
	const char *s = "Hello";
	char *substring = ft_substr(s, 3,2);
	int i = 0;
	printf("substring is:%s\n",substring);
	
	while (substring[i])
	{
		printf
	}
	
	return 0;
}
*/

/*
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*s_cpy;
	char	*copied;
	unsigned int	i;

	s_cpy = (char *)s;
	copied = (char *)malloc(ft_strlen())
}
*/

char	*ft_strjoin(const char	*str_f, const char	*str_s)
{
	unsigned int	i;
	unsigned int	j;
	char			*str_joined;

	i = 0;
	j = 0;
	str_joined = (char *)malloc((ft_strlen(str_f) + ft_strlen(str_s) + 1)
			* sizeof(char));
	if (!str_joined)
		return (NULL);
	while (str_f[i])
	{
		str_joined[i] = str_f[i];
		i++;
	}
	while (str_s[j])
	{
		str_joined[i + j] = str_s[j];
		j++;
	}
	str_joined[i + j] = '\0';
	return (str_joined);
}
/*
int	main(void)
{
	const char *s1 = "Hello";
	const char *s2 = "";
	const char *s3 = "";
	size_t strlen = ft_strlen(s2);
	char *str_joined = ft_strjoin(s1,s2);
	char *str_joined_v2 = ft_strjoin(s2,s3);
	printf("joined string is:%s\n", str_joined);
	printf("strlen of empty string:%zu\n", strlen);
	printf("joined string try two is: %s\n", str_joined_v2);

	return 0;
}
*/
