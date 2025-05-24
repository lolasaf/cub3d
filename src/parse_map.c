/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:26:00 by kforfoli          #+#    #+#             */
/*   Updated: 2025/05/24 19:11:08 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    err_msg(const char *msg)
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
        int len = ft_strlen(m_lines[i]);
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
    map[y][x] = 'X';
    flood_it(map, x + 1, y);
    flood_it(map, x - 1, y);
    flood_it(map, x, y + 1);
    flood_it(map, x, y- 1);
}

void check_borders(t_data *d, int rows, int cols)
{
    if (d->num[0] == 0 || d->num[0] == rows - 1 ||
                    d->num[1] == 0 || d->num[1] == cols - 1)
                    err_msg("Player cannot be in borders");
                    
}
int set_player(char c, int i, int j, t_data *data)
{
    if (!is_valid_char(c))
        err_msg("Error: Invalid character in map");
    if (is_player(c))
    {
        data->player = c;
        data->num[0] = i;
        data->num[1] = j;
        return 1;
    }
    return 0;
}

void pad_map(char **map, char **lines, int rows, int cols)
{
    int i = 0; // Row iterator

    while (i < rows) 
    {
        strcpy(map[i], lines[i]);
        int len = ft_strlen(lines[i]);
        int j = len; 

        while (j < cols) 
        {
            map[i][j] = ' ';
            j++;
        }
        i++;
    }
}

int find_player(char **map, int rows, int cols, t_data *data) 
{
    int p_count = 0;
    int i = 0;

    while (i < rows) 
    {
        int j = 0;
        while (j < cols) 
        {
            char c = map[i][j];
            if (set_player(c, i, j,data))
                p_count++;
            if (p_count != 0)
                check_borders(data, rows, cols);
            j++;
        }
        i++;
    }
    return p_count;
}

void ft_free_map(char **map) 
{
    if (map == NULL) 
        return;

    int i = 0;

    while (map[i] != NULL)
    {
        free(map[i]); 
        map[i] = NULL; 
        i++;          
    }

    free(map); 
    map = NULL;
}

char **init_map(char **lines, int count, t_data *data) 
{
    data->map_height = count;
    data->map_width = get_width(lines, count);

    char **map = calloc(data->map_height + 1, sizeof(char *));
    if (!map)
        err_msg("Memory allocation error for map rows");

    int i = 0;
    while (i < data->map_height) 
    {
        map[i] = calloc(data->map_width + 1, sizeof(char));
        if (!map[i])
        {
            ft_free_map(map);
            err_msg("Memory allocation error for map row content");
        }
        i++;
    }
    map[data->map_height] = NULL;
    return map;
}

char **pvmap(char **lines, int count, t_data *data) 
{
    if (!lines || count <= 0)
        err_msg("Invalid input to pvmap: lines are NULL or count is non-positive");

    char **map = init_map(lines, count, data);
    pad_map(map, lines, data->map_height, data->map_width);

    int p_count = find_player(map, data->map_height, data->map_width, data);
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
