/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:26:06 by kforfoli          #+#    #+#             */
/*   Updated: 2025/04/29 20:26:07 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int ft_parse_texture(char *line, t_data *data)
{
    char *trimmed = trim(line);
    static int i = 0;
    if (strncmp(trimmed, "NO", 2) == 0)
    {
        data->texture[0].identifier = strdup("NO");
        char *ptr = line + 2;
        while (*ptr && isspace((unsigned char)*ptr))
            ptr++;
        data->texture[0].path = strdup(ptr);
        i = i + 1;
    }
    if (strncmp(line, "SO", 2) == 0)
    {
        data->texture[1].identifier = strdup("SO");
        char *ptr = line + 2;
        while (*ptr && isspace((unsigned char)*ptr))
            ptr++;
        data->texture[1].path = strdup(ptr);
        i = i + 2;
    }
    if (strncmp(line, "WE", 2) == 0)
    {
        data->texture[2].identifier = strdup("WE");
        char *ptr = line + 2;
        while (*ptr && isspace((unsigned char)*ptr))
            ptr++;
        data->texture[2].path = strdup(ptr);
        i = i + 3;
    }
    if (strncmp(line, "EA", 2) == 0)
    {
        data->texture[3].identifier = strdup("EA");
        char *ptr = line + 2;
        while (*ptr && isspace((unsigned char)*ptr))
            ptr++;
        data->texture[3].path = strdup(ptr);
        i = i + 4;
    }
    if (i == 10)
        data->is_last++;
    return 1;
}