/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:26:06 by kforfoli          #+#    #+#             */
/*   Updated: 2025/05/24 06:14:31 by kforfoli         ###   ########.fr       */
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
    while(ft_isspace((unsigned char)*line))
        line++;
    if (*line == 0)
        return line;
    char *end = line + ft_strlen(line) -1;
    while(end > line && ft_isspace((unsigned char)*end))
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
    char *end = line + ft_strlen(line) - 1;
    while(end > line && ft_isspace((unsigned char)*end))
        end--;
    *(end + 1) = '\0';
    return line;

}
int set_texture(t_data *data, int i, char *path, char *str)
{
    int j = 1;
    char *nl = ft_strchr(path, '\n');
    if (nl)
        *nl = '\0';
    data->texture[i].identifier = ft_strdup(str);
    data->texture[i].path = ft_strdup(path);
    j = j + i;
    return j;
}   
int ft_parse_texture(char *token, char *line, t_data *data)
{
    char *trimmed = trim(line);

    static int i = 0;
    if (i == 10)
        err_msg("Duplicate texture detected");
    if (ft_strncmp(token, "NO", 2) == 0)
        i += set_texture(data, 0, trimmed, "NO"); //1
    if (ft_strncmp(token, "SO", 2) == 0)
        i += set_texture(data, 1, trimmed, "SO"); //2
    if (ft_strncmp(token, "WE", 2) == 0)
        i += set_texture(data, 2, trimmed, "WE");//3
    if (ft_strncmp(token, "EA", 2) == 0)
        i += set_texture(data, 3, trimmed, "EA");//4
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
    slash = ft_strrchr(path, '/');
    if (slash != NULL)
        base = slash + 1;
    else
        base = path;
    dot = ft_strrchr(base, '.');
    if (dot == NULL)
        err_msg("ERR:Not a valid texture");
    if (strcmp(dot, xpm) != 0)
        err_msg("ERR: Not a valid texture");
}

void ft_validate_textures(t_data *data)
{
    if (data->texture[0].path == NULL || data->texture[1].path == NULL || data->texture[2].path == NULL || data->texture[3].path == NULL)
        err_msg("Texture paths not provided");
    int i = 0;
    while (i < 4)
    {
        
        ft_check_xpm(data->texture[i].path, ".xpm");
        i++;
    }
}
