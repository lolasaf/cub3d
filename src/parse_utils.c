/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:47:18 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/31 19:31:20 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*trim(char *line)
{
	char	*end;

	while (ft_isspace((unsigned char)*line))
		line++;
	if (*line == 0)
		return (line);
	end = line + ft_strlen(line) - 1;
	while (end > line && ft_isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
	return (line);
}

char	*ft_trim(char *line)
{
	char	*end;

	while (line != NULL && ft_isspace((unsigned char)*line))
		line++;
	if (line == NULL)
		return (line);
	end = line + ft_strlen(line) - 1;
	while (end > line && ft_isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
	return (line);
}

/*checks if it is a .cub file*/
void	ft_ext_check(const char *path, const char *cub)
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
		err_msg("ERR: Not a valid file extension", NULL, NULL);
	if (ft_strncmp(dot, cub, 4) != 0)
		err_msg("ERR: Not a valid file extension", NULL, NULL);
}
