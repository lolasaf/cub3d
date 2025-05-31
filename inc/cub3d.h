/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:50:41 by wel-safa          #+#    #+#             */
/*   Updated: 2025/05/31 19:32:40 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <ctype.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <mlx_int.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define SCREEN_HEIGHT 960
# define SCREEN_WIDTH 1200
# define MAX_LINES 1000
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define ESC_KEY 65307
# define RIGHT_ARROW 65363
# define LEFT_ARROW 65361
# define SPACE_KEY 32
# define SCROLL_DOWN 5
# define SCROLL_UP 4
# define VERTICAL 1
# define HORIZONTAL 0
# define MAX_SPRITES 100
# define SPRITE_LOAD 7
# define SPRITE_RATIO 15

typedef struct s_texture		t_texture;
typedef enum e_tex				t_tex;
typedef struct s_color			t_color;
typedef struct s_build			t_build;
typedef struct s_data			t_data;
typedef struct s_game			t_game;
typedef struct s_sprite_sort	t_sprite_sort;
typedef struct s_ray			t_ray;
typedef enum e_type				t_type;
typedef struct s_imgp			t_imgp;
typedef struct s_press			t_press;
typedef struct s_textureobj		t_texture_object;

typedef enum e_tex
{
	TEX_NORTH,
	TEX_SOUTH,
	TEX_EAST,
	TEX_WEST
}	t_tex;

typedef struct s_sprite_sort
{
	double	dist;
	int		index;
}	t_sprite_sort;

struct s_texture
{
	char	*identifier;
	char	*path;
};

struct s_color
{
	char	type;
	int		rgb[3];
};

typedef struct s_imgp
{
	void	*img_ptr;
	char	*addr;
	int		bbp;
	int		line_length;
	int		endian;
}	t_imgp;

typedef struct s_press
{
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	rotate_l;
	bool	rotate_r;
}	t_press;

typedef struct s_textureobj
{
	int				width;
	int				height;
	unsigned int	*texture_addr[4];
	int				texture_bpp[4];
	int				texture_ll[4];
	int				texture_endian[4];
}	t_texture_object;

typedef struct s_sprite_load
{
	double	x;
	double	y;
	void	*img;
	int		id;
}	t_sprite;

typedef struct s_sprite_drawing
{
	double	t_x;
	double	t_y;
	int		s_sx;
	int		s_h;
	int		s_w;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		stripe_x;
}	t_sprite_props;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_imgp		*img;
	t_data		*conf;
	t_press		*keys;
	void		*texture_img[5];
	double		player_x;
	double		player_y;
	double		player_dir_x;
	double		player_dir_y;
	double		plane_x;
	double		plane_y;
	t_sprite	sprites[MAX_SPRITES];
	int			num_sprites;
	double		*z_buffer;
}	t_game;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	step_x;
	double	step_y;
	double	hit_x;
	double	hit_y;
	int		hit;
	int		side;
	double	perp_distance;
}	t_ray;

typedef struct s_draw
{
	int		col;
	int		texture;
	int		wall_height;
	int		og_draw_start;
	int		draw_start;
	int		draw_end;
	double	wall_x;
}	t_draw;

typedef struct s_data
{
	t_texture			texture[4];
	t_color				color[2];
	t_texture_object	*o;
	t_build				*build;
	char				**map;
	int					map_width;
	int					map_height;
	int					num[2];
	char				player;
	int					is_last;
}	t_data;

typedef struct s_build
{
	char	*map_lines[MAX_LINES];
	int		count;
}	t_build;

// cast_ray.c
void			cast_ray(t_game *game, double ray_dir_x,
					double ray_dir_y, int col);
void			init_ray(t_game *game, t_ray *ray);
void			ray_loop(t_game *game, t_ray *ray);
void			calc_steps(t_game *game, t_ray *ray);
void			compute_distance(t_game *game, t_ray *ray);

// draw_wall.c
void			draw_wall(t_game *game, t_ray *ray,
					t_draw *draw_vars);
void			draw_wall_column(t_game *game,
					t_draw *draw_vars, int tex_x);
void			assign_texture(t_ray *ray, t_draw *draw_vars);
void			calculate_wall_x(t_game *game, t_ray *ray,
					t_draw *draw_vars);
int				get_tex_x(t_game *game, t_draw *draw_vars);

// draw.c
void			draw(t_game *game, t_draw *draw_vars,
					t_ray *ray);
void			get_draw_vars(t_ray *ray, t_draw *draw_vars);
void			draw_floor(t_game *game, t_draw *draw_vars);
void			draw_ceiling(t_game *game, t_draw *draw_vars);
int				rgb_to_hex(int r, int g, int b);

// exit_game.c
void			free_map(t_data *conf);
void			free_build(t_build *build);
void			free_sprites(t_game *game);
int				exit_game(t_game *game);
void			print_menu(void);
void			print_poki(t_game *game);
void			print_done(void);
void			print_menu_err(void);

// exit_game_utils.c
void			free_block(void *block);
void			destroy_mlx(t_game *game);
void			destroy_buffer(t_game *game);
void			free_texture_vars(t_data *data);
void			free_textures(t_game *game);

// find_player.c
int				find_player(char **map, int rows, int cols,
					t_data *data);
int				set_player(char c, int i, int j, t_data *data);
void			check_borders(char **map, t_data *d, int rows,
					int cols);

// initialize.c
void			initialize_game(t_game *game, t_data *data);
t_press			*ft_init_keys(t_press *k);

// key_flags.c
int				ft_on_release(int kc, t_game *g);
int				ft_on_press(int kc, t_game *g);

// key_hooks.c
void			ft_mlx_hook_loop(t_game *game);
int				mouse_hook(int kc, int x, int y, t_game *game);
int				handle_keypress(int kc, t_game *game);
void			isnot_wall(t_game *game, double x, double y);

// minimap.c
void			draw_minimap(t_game *game);
void			draw_mini_grid(t_game *game, int scale, int x, int y);
void			draw_mini_player(t_game *game, int scale);

// move.c
void			ft_move_y(char c, t_game *game, double ms);
void			ft_move_z(char c, t_game *game, double rs);
void			ft_move_x(char c, t_game *game, double ms);

// parse_color_tok.c
void			parse_color_tok(char id, char *token, t_data *data,
					char *frline);
int				set_ceiling(t_data *data, int values[3]);
int				set_floor(t_data *data, int values[3]);

// parse_colors.c
int				parse_color(const char *str, int values[3]);
const char		*parse_single_value(const char *str, int *value);
const char		*skip_whitespace(const char *str);

// parse_map_utils.c
int				get_width(char **m_lines, int count);
int				is_valid_char(char c);
int				is_player(char c);
void			ft_free_map(char **map);

// parse_map.c
void			process_map(t_build *b, t_data *data);
char			**pvmap(char **lines, int count, t_data *data, t_build *b);
char			**init_map(char **lines, int count, t_data *data);
void			flood_it(char **map, int x, int y, t_data *data);

// parse_tandc.c
void			ft_colorortext(char *str, char *token, t_data *data,
					char *frline);
void			ft_parse_tandc(const char *line, t_data *data);

// parse_texture_load.c
void			mlx_texture_load(t_game *game);
void			set_dets(t_game *game);
void			load_texture_img(t_game *game);

// parse_textures.c
void			ft_validate_textures(t_data *data);
void			ft_check_xpm(char *path, const char *xpm, t_data *data);
int				ft_parse_texture(char *token, char *line, t_data *data,
					char *frline);
int				set_texture(t_data *data, int i, char *path, char *str);

// parse_utils.c
void			ft_ext_check(const char *path, const char *cub);
char			*ft_trim(char *line);
char			*trim(char *line);

// parse.c
void			parse(int argc, char **argv, t_data *data);
void			parse_func(int fd, t_build *b, t_data *data);
char			*check_map(char *is_line, int *fd, int *stop);
char			*newline(char *line, t_data *d, int *fd);
char			*add_map_line(t_build *assmbl, const char *line, t_data *data,
					int *fd);

// player.c
void			ft_player_orientation(t_game *g);
void			ew(t_game *g);
void			ns(t_game *g);

// render_game.c
void			render_game(t_game *game);

// utils.c
int				ft_isspace(char c);
void			put_pixel_to_img(t_game *game, int x, int y, int color);
char			*ft_strncpy(char *dest, const char *src, size_t n);
void			clear_image(t_game *game);
void			err_msg(const char *msg, void *build, void *conf);

// sprites
void			ft_init_sprites(t_game *g);
void			mlx_sprite_load(t_game *g);
void			ft_sort(t_sprite_sort *to_sort, int count);
void			get_vertical_prop(t_sprite_props *prop);
void			get_horizonatal_prop(t_sprite_props *prop);
void			draw_stripe(t_game *game, t_img *sprite_tex, 
					t_sprite_props *prop, int tex_x);
void			single_sprite_render(t_game *g, t_img *sprite_tex,
					t_sprite_props *prop);
void			render_sprites(t_sprite_sort *to_sort, t_game *g);
void			handle_sprites(t_game *g);
int				ft_counter(t_game *g);
void			ft_check(double *b_x, double *b_y, t_game *g, char c);
int				ft_set(double *b_x, double *b_y, t_game *g, int i);
void			ft_init_sprites(t_game *g);
void			general_destroy(t_game *g);
t_sprite_props	calc_properties(t_game *g, t_sprite *s, double *catch);
int				fake_random(int seed, int a, int b);
void			draw_mini_sprite(t_game *game, int px, int py, int scale);
void			ft_destroy_sprite(t_game *game);

#endif