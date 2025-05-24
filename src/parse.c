/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:22:46 by kforfoli          #+#    #+#             */
/*   Updated: 2025/05/24 19:11:28 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *ft_strncpy(char *dest, const char *src, size_t n) 
{
    size_t i = 0;

    while (i < n && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n) 
    {
        dest[i] = '\0';
        i++;
    }
    return dest;
}

void ft_colorortext(char *str, char *token, t_data *data)
{
    if (ft_strncmp(token, "NO", 2) == 0 || ft_strncmp(token, "SO", 2) == 0 || ft_strncmp(token, "WE", 2) == 0 || ft_strncmp(token, "EA", 2) == 0)
    {
        ft_parse_texture(token, (char *)str, data);
        free(token);
        return;
    }
    if (token[0] == 'F' || token[0] == 'C')
    {
        parse_color_tok(token[0],(char *)str, data);
        free(token);
        return;
    }
    free(token);
}

void ft_parse_tandc(const char *line, t_data *data)
{
    const char *p = line;
    const char *another = NULL;
    while(*p)
    {
        while(*p && ft_isspace((unsigned char)*p))
            p++;
        if (!*p)
            break;
        const char *token_start = p;
        while (*p && !ft_isspace((unsigned char)*p))
            p++;
        int token_len = p - token_start;
        char *token = malloc(token_len + 1);
        if (!token)
            err_msg("Memory allocation failure");
        ft_strncpy(token, token_start, token_len);
        // ft_strlcpy(token, token_start, (size_t)token);
        token[token_len] = '\0';
        another = p;
        ft_colorortext((char *)another, token, data);
    }
}

char *add_map_line(t_build *assemble, const char *line, t_data *data,int *fd)
{
    char *cpy = (char *)line;
    char *next = get_next_line(*fd);
    if (assemble->count >= MAX_LINES)
    {
        free(next);
        err_msg("Too many lines");
    }
    if (ft_strchr(cpy, '\n') != NULL)
    {
        int distance = ft_strchr(cpy, '\n') - cpy;
        cpy[distance] = '\0';
    }
    assemble->map_lines[assemble->count] = ft_strdup(cpy);
    free(cpy);
    if (!assemble->map_lines[assemble->count])
        err_msg("ft_strdup failed");
    assemble->count++;
    if (next == NULL || *next == '\n')
        data->is_last++;
    return next;
}

/*checks if it is a .cub file*/
void ft_ext_check(const char *path, const char *cub)
{
    const char *base;
    const char *slash;
    const char *dot;

    slash = ft_strrchr(path, '/'); // is function allowed?
    if (slash != NULL)
        base = slash + 1;
    else
        base = path;
    dot = ft_strrchr(base, '.'); // is function allowed?
    if (dot == NULL)
        err_msg("ERR: Not a valid file extension");
    if (strcmp(dot, cub) != 0)
        err_msg("ERR: Not a valid file extension");
}
