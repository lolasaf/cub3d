/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:22:46 by kforfoli          #+#    #+#             */
/*   Updated: 2025/05/19 20:00:01 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_parse_tandc(const char *line, t_data *data)
{
    const char *p = line;
    const char *another = NULL;
    while(*p)
    {
        while(*p && isspace((unsigned char)*p))
            p++;
        if (!*p)
            break;
        const char *token_start = p;
        while (*p && !isspace((unsigned char)*p))
            p++;
        int token_len = p - token_start;
        char *token = malloc(token_len + 1);
        if (!token)
            err_msg("Memory allocation failure");
        strncpy(token, token_start, token_len);
        token[token_len] = '\0';
        another = p;
        if (strncmp(token, "NO", 2) == 0 || strncmp(token, "SO", 2) == 0 || strncmp(token, "WE", 2) == 0 || strncmp(token, "EA", 2) == 0)
        {
            ft_parse_texture(token, (char *)another, data);
            free(token);
            return;
        }
        //ft_parse_texture(token, (char *)another, data);
        if (token[0] == 'F' || token[0] == 'C')
        {
            parse_color_tok(token[0],(char *)another, data);
            free(token);
            return;
        }
        free(token);
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
    if (strchr(cpy, '\n') != NULL)
    {
        int distance = strchr(cpy, '\n') - cpy;
        cpy[distance] = '\0';
    }
    assemble->map_lines[assemble->count] = strdup(cpy);
    free(cpy);
    if (!assemble->map_lines[assemble->count])
        err_msg("Strdup failed");
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

    slash = strrchr(path, '/'); // is function allowed?
    if (slash != NULL)
        base = slash + 1;
    else
        base = path;
    dot = strrchr(base, '.'); // is function allowed?
    if (dot == NULL)
        err_msg("ERR: Not a valid file extension");
    if (strcmp(dot, cub) != 0)
        err_msg("ERR: Not a valid file extension");
}
