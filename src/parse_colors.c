/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_clrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:25:54 by kforfoli          #+#    #+#             */
/*   Updated: 2025/04/29 20:25:55 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_color(const char *str, int values[3])
{
    int i = 0;
    const char *p = str;
    while (i < 3)
    {
        while(*p && isspace((unsigned char)*p))
            p++;
        if (!isdigit((unsigned char)*p))
            return 0;
        int num = 0;
        while(*p && isdigit((unsigned char) *p))
        {
            num = num * 10 + (*p - '0');
            p++;
        }
        values[i] = num;

        while (*p &&isspace((unsigned char)*p))
            p++;
        if(i < 3)
        {
            if (*p != ',' && *p != '\0')
                return 0;
            p++;
        }
        i++;
    }
    while (*p && isspace((unsigned char) *p))
        p++;
    if (*p != '\0' && *p != '\n')
        return 0;
    return 1;
}

void parse_color_tok(char *token, t_data *data)
{
    static int j = 0;
    token = trim(token);
    if (*token != 'F' && *token != 'C')
        return;
    char id = *token;
    token++;
    token = trim(token);
    int values[3] = {0, 0, 0};
    if (!parse_color(token, values))
    {
        int i = 0;
        while(values[i])
        {
            printf("%d\n", values[i]);
            i++;
        }
        err_msg("Error! Failed to parse color values!");
    }
    int i = 0;
    while (i < 3)
    {
        if (values[i] < 0 || values[i] > 255)
            err_msg("Error: Color values out of range");
        i++;
    }
    if (id == 'F')
    {
        data->color[0].type = 'F';
        data->color[0].rgb[0] = values[0];
        data->color[0].rgb[1] = values[1];
        data->color[0].rgb[2] = values[2];
        j = j + 1;
    }
    if (id == 'C')
    {
        data->color[1].type = 'C';
        data->color[1].rgb[0] = values[0];
        data->color[1].rgb[1] = values[1];
        data->color[1].rgb[2] = values[2];
        j = j + 2;
    }
    if (j == 3)
        data->is_last++;
}

