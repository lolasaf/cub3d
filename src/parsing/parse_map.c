#include "parse_again.h"

void err_msg(const char *msg)
{
    printf("$%s\n");
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
    }
    return max;
}

void enclosed(char **map, int rows, int cols, int x, int y)
{
    if (x < 0 || x >= rows || y < 0 || y >= cols)
        return;
    if (map[x][y] == '1' || map[x][y] == OUTSIDE_MARK) return;
    map[x][y] = OUTSIDE_MARK;
    enclosed(map, rows, cols, x - 1, y);
    enclosed(map, rows, cols, x + 1, y);
    enclosed(map, rows, cols, x, y - 1);
    enclosed(map, rows, cols, x, y + 1);
}

char **pvmap(char **lines, int count)
{
    int p_count = 0;
    int rows = count;
    int cols = get_width(lines, count);


    char **map = malloc(rows * sizeof(char *));
    if (!map)
        err_msg("Memory allocation error");
    int i = 0;
    while (i < rows)
    {
        map[i] = malloc((cols + 1) * sizeof(char));
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
        map[i][cols] = '\0';
        i++;
    }
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
                p_count++;
            j++;
        }
        i++;
    }
    if (p_count != 1)
        err_msg("Error: Map must contain exactly one player position");
    
    i = 0;

    while (i < rows)
    {
        if (map[i][0] != '1') enclosed(map, rows, cols, i, 0);
        if (map[i][cols - 1] != '1') enclosed(map, rows, cols, i, cols - 1);
        i++;
    }
    int j = 0;
    while (j < cols)
    {
        if (map[0][j] != '1') enclosed(map, rows, cols, 0, j);
        if (map[rows - 1][j] != '1') enclosed(map, rows, cols, rows - 1, j);
        j++;
    }

    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            if (map[i][j] == OUTSIDE_MARK)
                err_msg("Error! Map is not properly enclosed");
    return map;
}

void process_map(char **map_lines, int count, t_data *data)
{
    char **valid_map = pvmap(map_lines, count);
    data->map = valid_map;
}