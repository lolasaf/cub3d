/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:54:03 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/27 17:21:32 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char	*skip_whitespace(const char *str)
{
	while (*str && ft_isspace((unsigned char)*str))
		str++;
	return (str);
}

const char	*parse_single_value(const char *str, int *value)
{
	str = skip_whitespace(str);
	if (!ft_isdigit((unsigned char)*str))
		return (NULL);
	*value = 0;
	while (*str && ft_isdigit((unsigned char)*str))
	{
		*value = *value * 10 + (*str - '0');
		str++;
	}
	return (str);
}

int	parse_color(const char *str, int values[3])
{
	const char	*p;
	int			i;

	i = 0;
	p = str;
	while (i < 3)
	{
		p = parse_single_value(p, &values[i]);
		if (p == NULL)
			return (0);
		p = skip_whitespace(p);
		if (i < 2)
		{
			if (*p != ',')
				return (0);
			p++;
		}
		i++;
	}
	return (1);
}
