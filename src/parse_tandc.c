/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tandc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:40:08 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/25 01:23:55 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_colorortext(char *str, char *token, t_data *data)
{
	if (ft_strncmp(token, "NO", 2) == 0
		|| ft_strncmp(token, "SO", 2) == 0 || ft_strncmp(token, "WE", 2) == 0
		|| ft_strncmp(token, "EA", 2) == 0)
	{
		ft_parse_texture(token, (char *)str, data);
		free(token);
		return ;
	}
	if (token[0] == 'F' || token[0] == 'C')
	{
		parse_color_tok(token[0], (char *)str, data);
		free(token);
		return ;
	}
	free(token);
}

void	ft_parse_tandc(const char *line, t_data *data)
{
	const char	*p;
	const char	*another;
	const char	*token_start;
	int			token_len;
	char		*token;

	p = line;
	another = NULL;
	while (*p)
	{
		while (*p && ft_isspace((unsigned char)*p))
			p++;
		if (!*p)
			break ;
		token_start = p;
		while (*p && !ft_isspace((unsigned char)*p))
			p++;
		token_len = p - token_start;
		token = ft_calloc(token_len + 1, sizeof(char));
		if (!token)
			err_msg("Memory allocation failure");
		ft_strncpy(token, token_start, token_len);
		another = p;
		ft_colorortext((char *)another, token, data);
	}
}
