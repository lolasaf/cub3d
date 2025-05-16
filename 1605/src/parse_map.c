/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:26:00 by kforfoli          #+#    #+#             */
/*   Updated: 2025/05/13 16:17:22 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void err_msg(const char *msg)
{
    printf("$error %s\n", msg); // check this
    exit(1);
}

int is_player(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int is_valid_char(char c)
{
    return (c == '0' || c == '1' || is_player(c) || c == ' ');
}

int get_width(char **m_lines, int count)
{
    int max = 0;
    int i = 0;
    while(i < count)
    {
        int len = strlen(m_lines[i]);
        if (len > max)
            max = len;
        i++;
    }
    return max;
}


void flood_it(char **map, int x, int y)
{
    if (x < 0 || y < 0 || map[y] == NULL || map[y][x] == '\0')
        err_msg("Map is not properly closed");
    if (map[y][x] == '1' || map[y][x] == 'X')
        return;
    //if (map[y][x] == ' ')
        //err_msg("Map is not properly closed");
    map[y][x] = 'X';
    flood_it(map, x + 1, y);
    flood_it(map, x - 1, y);
    flood_it(map, x, y + 1);
    flood_it(map, x, y- 1);
}

char **pvmap(char **lines, int count, t_data *data)
{
    int p_count = 0;
    int rows = count;
    int cols = get_width(lines, count);
    data->map_width = cols;
    data->map_height = rows;
    char **map = calloc(rows + 1, sizeof(char *));
    if (!map)
        err_msg("Memory allocation error");
    int i = 0;
    while (i < rows)
    {
        map[i] = calloc(cols + 1, sizeof(char));
        if (!map[i])
            err_msg("Memory allocation error");
        int len = strlen(lines[i]);
        strcpy(map[i], lines[i]);
        int j = len;
        while (j < cols)
        {
            map[i][j] = ' ';
            j++;
        }
        i++;
    }
    map[rows] = NULL;
    i = 0;
    while (i < rows)
    {
        int j = 0;
        while (j < cols)
        {
            char c = map[i][j];
            if (!is_valid_char(c))
                err_msg("Error: Invalid character in map");
            if (is_player(c))
            {
                data->player = c;
                data->num[0] = i;
                data->num[1] = j;
                p_count++;
                if (data->num[0] == 0 || data->num[1] == 0)
                    err_msg("Player cannot be in borders");
            }
            j++;
        }
        i++;
    }
    if (p_count != 1)
        err_msg("Error: Map must contain exactly one player position");
    flood_it(map, data->num[1], data->num[0]);
    return map;
}

void process_map(t_build *b, t_data *data)
{
    char **valid = pvmap(b->map_lines, b->count, data);
    data->map = valid;
}
