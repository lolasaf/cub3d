#ifndef CUBE_H
#define CUBE_H

#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include "libft.h"
#include <mlx.h>

typedef enum e_type
{
    NO_TEXTURE,
    SO_TEXTURE,
    WE_TEXTURE,
    EA_TEXTURE,
    FLOOR_COLOR,
    CEILING_COLOR,
    MAP
} t_type;

typedef struct s_config t_config;
typedef struct s_game my_game;
typedef struct s_ray t_ray;
typedef enum e_type t_type;
typedef struct s_img t_img;

typedef struct s_img
{
    void    *img_ptr;
    char    *addr;
    int     bbp; // bits per pixel
    int     line_length;
    int     endian;
} t_img;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *img;
    void    *txt_img[4];
    int     width;
    int     height;
    t_config *conf;
    double p_x;
    double  p_y;
    double  p_dir_x;
    double  p_dir_y;
    double plane_x;
    double plane_y;
    double *z_buffer;
} my_game;

typedef struct s_ray
{
    double dir_x;
    double dir_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    double perp_wall;
    int step_x;
    int step_y;
    int hit;
    int side;
} t_ray;

struct s_config
{
    char *textures[4];
    int floor_color[3];
    int ceiling_color[3];
    char **map;
    int map_lines;
};

void parse_file(const char *f_name, t_config *config);
void parse_texture(char *line, t_type type, t_config *config);
void parse_color(char *line, t_type type, t_config *config);
void add_map_line(char *line, t_config *config);
void trim_whitespace(char *str);
void validate_config(t_config *config);
void free_config(t_config *config);

void draw_minimap(t_config *config);

#endif