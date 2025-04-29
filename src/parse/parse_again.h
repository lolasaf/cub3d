# ifndef PARSE_AGAIN_H
# define PARSE_AGAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../../lib/libft/libft.h"

#define MAX_LINES 1000

typedef struct s_texture t_texture;
typedef struct s_color t_color;
typedef struct s_build t_build;


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

typedef struct s_data
{
    t_texture texture[4];
    t_color color[2];
    char **map;
    int map_width;
    int map_height;
    int num[2];
    int is_last;
}t_data;


struct s_build{
    char *map_lines[MAX_LINES];
    int count;
};

void transform_sec(char *map);
void err_msg(const char *msg);
char *trim(char *line);
int ft_parse_texture(char *line, t_data *data);
int parse_color(const char *str, int values[3]);
void parse_color_tok(char *token, t_data *data);
void process_map(t_build *b, t_data *data);
void transform(t_build *a);
void ft_print(char **map);
void flood_it(char **map, int x, int y);
// void process_map(char **map_lines, int count, t_data *data);

#endif