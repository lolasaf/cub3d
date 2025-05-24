/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:25:54 by kforfoli          #+#    #+#             */
/*   Updated: 2025/05/24 04:44:13 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


const char *skip_whitespace(const char *str) 
{
    while (*str && ft_isspace((unsigned char)*str))
        str++;
    return str;
}

const char *parse_single_value(const char *str, int *value) 
{
    str = skip_whitespace(str); // Skip leading whitespace
    if (!ft_isdigit((unsigned char)*str))
        return NULL;
    *value = 0;
    while (*str && ft_isdigit((unsigned char)*str)) 
    {
        *value = *value * 10 + (*str - '0');
        str++;
    }
    return str;
}

int parse_color(const char *str, int values[3]) 
{
    const char *p = str;
    int i = 0;

    while (i < 3)
    {
        p = parse_single_value(p, &values[i]);
        if (p == NULL)
            return 0;
        p = skip_whitespace(p); 
        if (i < 2) 
        {
            if (*p != ',')
                return 0;
            p++;
        }
        i++;
    }
    return 1;
}

int set_floor(t_data *data, int values[3])
{
    data->color[0].type = 'F';
    data->color[0].rgb[0] = values[0];
    data->color[0].rgb[1] = values[1];
    data->color[0].rgb[2] = values[2];
    return 1;
}

int set_ceiling(t_data *data, int values[3])
{
    data->color[1].type = 'C';
    data->color[1].rgb[0] = values[0];
    data->color[1].rgb[1] = values[1];
    data->color[1].rgb[2] = values[2];
    return 2;
}

void parse_color_tok(char id, char *token, t_data *data)
{
    static int j;
    
    token = trim(token);
    int values[3] = {0, 0, 0};
    if (!parse_color(token, values))
        err_msg("Error! Failed to parse color values!");
    int i = 0;
    while (i < 3)
    {
        if (values[i] < 0 || values[i] > 255)
            err_msg("Error: Color values out of range");
        i++;
    }
    if (id == 'F')
        j += set_floor(data, values);
    else if (id == 'C')
        j += set_ceiling(data, values);
    if (j == 3)
        data->is_last++;
}