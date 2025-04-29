#ifndef CUBE_H
#define CUBE_H

//#define TEXTURE_WIDTH 64
//#define TEXTURE_HEIGHT 64
#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640
#define MAX_LINES 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include "libft.h"
#include <mlx.h>
#include <math.h>


typedef struct s_texture t_texture;
typedef struct s_color t_color;
typedef struct s_build t_build;

typedef struct s_data t_data;
typedef struct s_game my_game;
typedef struct s_ray t_ray;
typedef enum e_type t_type;
typedef struct s_img t_img;




struct s_texture
{
    char *identifier;
    char *path;
};
struct s_color
{
    char type;
    int rgb[3];
};


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
    t_img    *img;
    //void    *txt_img[4];
    //int     width;
    //int     height;
    t_data *conf;
    double player_x;
    double  player_y;
    double  player_dir_x;
    double  player_dir_y;
    double plane_x;
    double plane_y;
    //double *z_buffer;
} my_game;

typedef struct s_ray
{
    double dir_x;
    double dir_y;
    double step_x;
    double step_y;
    double hit_x;
    double hit_y;
    int hit;
    int side;
    int map_x;
    int map_y;
    double  perp_distance;
    //double side_dist_x;
    //double side_dist_y;
    //double delta_dist_x;
    //double delta_dist_y;
    //double perp_wall;
} t_ray;

typedef struct s_data
{
    t_texture texture[4];
    t_color color[2];
    char **map;
    int map_width;
    int map_height;
    int num[2];
    int is_last;
} t_data;

struct s_build{
    char *map_lines[MAX_LINES];
    int count; // map height
};


///////////////// OLD FUNCTIONS

// void parse_file(const char *f_name, t_data *data);
// void parse_texture(char *line, t_type type, t_data *data);
// void parse_color(char *line, t_type type, t_data *data);
// void add_map_line(char *line, t_data *data);
// void trim_whitespace(char *str);
// void validate_config(t_data *data);
// void free_config(t_data *data);

// Sandy's functions
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
void ft_ext_check(const char *path, const char *cub);
void add_map_line(t_build *assemble, const char *line, t_data *data);
void ft_parse_tandc(const char *line, t_data *data);



// lola's functions
void    draw_minimap(t_data *data);
void    put_pixel_to_img(void *mlx, t_img *img, int x, int y, int color);
void    render_map(my_game *game);
void	cast_ray(my_game *game, double ray_dir_x, double ray_dir_y, int col);

#endif