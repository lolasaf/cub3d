#include "cube.h"

void    validate_map(t_config *conf)
{
    for(int i = 0; i < conf->map_lines; i++)
    {
        int len = strlen(conf->map[i]);
        for (int j = 0; j < len; j++)
        {
            char c = conf->map[i][j];
            if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ')
            {
                fprintf(stderr, "Error\nInvalid map character '%c' at line %d, col %d\n", 
                        c, i + 1, j + 1);
                exit(EXIT_FAILURE);
            }
        }
    }
}

void    ft_player_pos(t_config *conf)
{
    int     count = 0;
    for(int i = 0; i < conf->map_lines; i++)
    {
        int len = strlen(conf->map[i]);
        for (int j = 0; j < len; j++)
        {
            char c = conf->map[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                count++;
        }
    }
    if (count != 1)
    {
        fprintf(stderr, "Error\nMap must have exactly one player position.\n");
        exit(EXIT_FAILURE);
    }
}

void    ft_find_pos(t_config *conf, int *pi, int *pj)
{
    for (int i = 0; i < conf->map_lines; i++)
    {
        int len = strlen(conf->map[i]);
        for(int j = 0; j < len; j++)
        {
            char c = conf->map[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                *pi = i;
                *pj = j;
                return;
            }
        }
    }
}

void    ft_floodfill(t_config *conf, int i, int j, int **visit, int *err_flg)
{
    if (i < 0 || i >= conf->map_lines)
    {
        *err_flg = 1;
        return;
    }
    int row = strlen(conf->map[i]);
    if (j < 0 || j >= row)
    {
        *err_flg = 1;
        return;
    }
    if (visit[i][j])
        return;
    char c = conf->map[i][j];
    if (c == '1')
        return;
    if (c == ' ')
    {
        *err_flg = 1;
        return;
    }
    visit[i][j] = 1;
    ft_floodfill(conf, i - 1, j, visit, err_flg);
    ft_floodfill(conf, i + 1, j, visit, err_flg);
    ft_floodfill(conf, i, j - 1, visit, err_flg);
    ft_floodfill(conf, i, j + 1, visit, err_flg);
}

void    ft_validate_map(t_config *conf)
{
    int pi = -1;
    int pj = -1;
    ft_find_pos(conf, &pi, &pj);
    if (pi == -1 || pj == -1)
    {
        fprintf(stderr, "Error\no player position found during flood fill.\n");
        exit(EXIT_FAILURE);
    }
    
    int **visit = malloc (sizeof(int*) * conf->map_lines);
    if (!visit)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < conf->map_lines; i++)
    {
        int len = strlen(conf->map[i]);
        visit[i] = calloc(len, sizeof(int));
        if (!visit[i])
        {
            perror("calloc failed");
            exit(EXIT_FAILURE);
        }
    }
    int err_flg = 0;
    ft_floodfill(conf, pi, pj, visit, &err_flg);
    for (int i = 0; i < conf->map_lines; i++)
        free(visit[i]);
    free(visit);
    
    if (err_flg)
    {
        fprintf(stderr, "Error\nMap is not closed\n");
        exit(EXIT_FAILURE);
    }
}

void    validate_config(t_config *conf)
{
    for(int i = 0; i < 4; i++)
    {
        if (conf->textures[i] == NULL)
        {
            // fprintf(stderr, "Error\nMissing texture for index %d\n");
            exit(EXIT_FAILURE);
        }
    }
    if (conf->map_lines == 0 || conf->map == NULL)
    {
        fprintf(stderr, "Error\nNo map data found\n");
        exit(EXIT_FAILURE);
    }
    
    validate_map(conf);
    ft_player_pos(conf);
    ft_validate_map(conf);
}
