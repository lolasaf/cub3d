/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:26:06 by kforfoli          #+#    #+#             */
/*   Updated: 2025/05/18 20:39:38 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     ft_isspace(char c)
{
    if (c == ' ' || c == '\t' || c == '\v' || c == '\f')
        return 1;
    return 0;
}

char *trim(char *line)
{
    while(isspace((unsigned char)*line))
        line++;
    if (*line == 0)
        return line;
    char *end = line + strlen(line) -1;
    while(end > line && isspace((unsigned char)*end))
        end--;
    *(end + 1) = '\0';
    return line;
}

char *ft_trim(char *line)
{
    while(line != NULL && ft_isspace((unsigned char)*line))
        line++;
    if (line == NULL)
        return line;
    char *end = line + strlen(line) - 1;
    while(end > line && ft_isspace((unsigned char)*end))
        end--;
    *(end + 1) = '\0';
    return line;

}

int ft_parse_texture(char *token, char *line, t_data *data)
{
    char *trimmed = trim(line);
    static int i = 0;
    if (i == 10)
        err_msg("Duplicate texture detected");
    if (strncmp(token, "NO", 2) == 0)
    {
        data->texture[0].identifier = strdup("NO");
        data->texture[0].path = strdup(trimmed);
        i = i + 1;
    }
    if (strncmp(token, "SO", 2) == 0)
    {
        data->texture[1].identifier = strdup("SO");
        data->texture[1].path = strdup(trimmed);
        i = i + 2;
    }
    if (strncmp(token, "WE", 2) == 0)
    {
        data->texture[2].identifier = strdup("WE");
        data->texture[2].path = strdup(trimmed);
        i = i + 3;
    }
    if (strncmp(token, "EA", 2) == 0)
    {
        data->texture[3].identifier = strdup("EA");
        data->texture[3].path = strdup(trimmed);
        i = i + 4;
    }
    if (i == 10)
        data->is_last++;
    return 1;
}

void ft_check_xpm(char *path, const char *xpm)
{
    const char *base;
    const char *slash;
    const char *dot;
    //"../../wfwe.cub"
    //"rhfwhfpwrpg.cub"
    slash = strrchr(path, '/');
    if (slash != NULL)
        base = slash + 1;
    else
        base = path;
    dot = strrchr(base, '.');
    if (dot == NULL)
        err_msg("ERR:Not a valid texture");
    if (strcmp(dot, xpm) != 0)
        err_msg("ERR: Not a valid texture");
}

void ft_validate_textures(t_data *data)
{
    //extension must be .xpm(2)
    //see if all texture paths have a path(1)
    //check if path exists(3)
    if (data->texture[0].path == NULL || data->texture[1].path == NULL || data->texture[2].path == NULL || data->texture[3].path == NULL)
        err_msg("Texture paths not provided");
    int i = 0;
    while (i < 4)
    {
        ft_check_xpm(data->texture[i].path, ".xpm");
        i++;
    }
    /*
    int fd[4];
    i = 0;
    while(i < 4)
    {
        fd[i] = open(data->texture[i].path,O_RDONLY);
        if (fd[i] < 0)
            err_msg("Couldn't find texture file");
        i++;
    }
    */
}
