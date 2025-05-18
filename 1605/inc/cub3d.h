#ifndef CUBE_H
#define CUBE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include "libft.h"
#include <mlx.h>
#include <math.h>
#include <stdbool.h>

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640
#define MAX_LINES 1000
#define W_KEY 119
#define S_KEY 115
#define A_KEY 97
#define D_KEY 100
#define ESC_KEY 65307
#define RIGHT_ARROW 65363
#define LEFT_ARROW 65361



typedef struct s_texture t_texture;
typedef enum e_tex t_tex;
typedef struct s_color t_color;
typedef struct s_build t_build;
typedef struct s_data t_data;
typedef struct s_game my_game;
typedef struct s_ray t_ray;
typedef enum e_type t_type;
typedef struct s_img t_img;
typedef struct s_press t_press;
typedef struct s_textureobj t_texture_object;


typedef enum e_tex
{
    TEX_NORTH,
    TEX_SOUTH,
    TEX_EAST,
    TEX_WEST
} t_tex;

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

typedef struct s_press
{
    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;
    bool rotate_l;
    bool rotate_r;
} t_press;

typedef struct s_textureobj
{
    int width;
    int height;
    unsigned int *texture_addr[4];
    int texture_bpp[4];
    int texture_ll[4];
    int texture_endian[4];
} t_texture_object;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    t_img    *img;
    t_data *conf;
    t_press *keys;
    void    *texture_img[4];
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
    int map_x;
    int map_y;
    double delta_dist_x;
    double delta_dist_y;
    double side_dist_x;
    double side_dist_y;
    double step_x;
    double step_y;
    double hit_x;
    double hit_y;
    int hit;
    int side;
    double  perp_distance;
} t_ray;

typedef struct s_draw
{
    int     col;
    int     texture;
    int     wall_height;
    int     og_draw_start;
    int     draw_start;
    int     draw_end;
    double  wall_x;
} t_draw;

typedef struct s_data
{
    t_texture texture[4];
    t_color color[2];
    t_texture_object *o;
    char **map;
    int map_width;
    int map_height;
    int num[2]; //double?
    char player;
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
t_press* ft_init_keys(t_press *k);
void transform_sec(char *map);
void err_msg(const char *msg);
char *ft_trim(char *line);
char *trim(char *line);
int ft_parse_texture(char *token, char *line, t_data *data);
int parse_color(const char *str, int values[3]);
void parse_color_tok(char id,char *token, t_data *data);
void process_map(t_build *b, t_data *data);
void transform(t_build *a);
//void ft_print(char **map);
void flood_it(char **map, int x, int y);
void ft_ext_check(const char *path, const char *cub);
char *add_map_line(t_build *assemble, const char *line, t_data *data, int *fd);
void ft_parse_tandc(const char *line, t_data *data);
void ft_validate_textures(t_data *data);
int ft_on_press(int kc, my_game *g);
int ft_on_release(int kc, my_game *g);
void    ft_player_orientation(my_game *g);
void clear_image(t_img *img);

// t_press* ft_init_keys(t_press *k);

int     rgb_to_hex(int r, int g, int b);

// lola's functions
void    put_pixel_to_img(void *mlx, t_img *img, int x, int y, int color);
void	cast_ray(my_game *game, double ray_dir_x, double ray_dir_y, int col);
void	init_ray(my_game *game, t_ray *ray);
void    ray_loop(my_game *game, t_ray *ray);
void	calc_steps(my_game *game, t_ray *ray);
void	compute_distance(my_game *game, t_ray *ray);
void	draw(my_game *game, t_draw *draw_vars, t_ray *ray);
void    get_draw_vars(t_ray *ray, t_draw *draw_vars);
void    draw_floor(my_game *game, t_draw *draw_vars);
void    draw_ceiling(my_game *game, t_draw *draw_vars);
void	draw_wall(my_game *game, t_ray *ray, t_draw *draw_vars);
void	draw_wall_column(my_game *game, t_draw *draw_vars, int tex_x);
void	assign_texture(t_ray *ray, t_draw *draw_vars);
void	calculate_wall_x(my_game *game, t_ray *ray, t_draw *draw_vars);
int     get_tex_x(my_game *game, t_draw *draw_vars);
void    render_map(my_game *game);
void    draw_minimap(my_game *game);
void    handle_esc(my_game *game);

#endif