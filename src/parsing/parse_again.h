# ifndef PARSE_AGAIN_H
# define PARSE_AGAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define OUTSIDE_MARK '0'

typedef struct s_texture t_texture;
typedef struct s_color t_color;
typedef struct s_map t_map;

typedef struct s_data
{
    t_texture texture[4];
    t_color color[2];
    t_map *map;
    int is_last;
}t_data;

struct s_texture
{
    char *identifier;
    char *path;
};

struct s_color
{
    char type;
    int rbg[3];
};

struct s_map
{
    int is_last;
    char **map;
    int map_lines;
    int pos[2];
    int has_space;
};

void err_msg(const char *msg);
char *trim(char *line);
int ft_parse_texture(char *line, t_data *data);
int parse_color(const char *str, int values[3]);

#endif