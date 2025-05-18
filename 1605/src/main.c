/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:18:24 by kforfoli          #+#    #+#             */
/*   Updated: 2025/05/18 21:28:02 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void printing_shit(t_build *b, t_data *data)
{
    int i = 0;
    printf("Map before validation\n");
    while (b->map_lines[i])
        printf("%s\n", b->map_lines[i++]);
    printf("Textures:\n");
    printf("NO: %s\n", data->texture[0].path);
    printf("SO: %s\n", data->texture[1].path);
    printf("WE: %s\n", data->texture[2].path);
    printf("EA: %s\n", data->texture[3].path);
    printf("Floor color: %d, %d, %d\n", data->color[0].rgb[0], data->color[0].rgb[1], data->color[0].rgb[2]);
    printf("Ceiling color: %d, %d, %d\n", data->color[1].rgb[0], data->color[1].rgb[1], data->color[1].rgb[2]);
    printf("Map after validation (%d lines):\n", data->map_height);
    i = 0;
    while(data->map[i])
        printf("%s\n", data->map[i++]);
}*/
/*void ft_print(char **map)
{
    int i = 0;
    while(map[i] != NULL)
    {
        printf("%s\n", map[i]);
        i++;
    }
}*/

void mlx_texture_load(my_game *game)
{
    game->texture_img[0] =
        mlx_xpm_file_to_image(game->mlx, game->conf->texture[0].path, &game->conf->o->width, &game->conf->o->height);
    game->texture_img[1] =
        mlx_xpm_file_to_image(game->mlx, game->conf->texture[1].path, &game->conf->o->width, &game->conf->o->height);
    game->texture_img[2] =
        mlx_xpm_file_to_image(game->mlx, game->conf->texture[2].path, &game->conf->o->width, &game->conf->o->height);
    game->texture_img[3] =
        mlx_xpm_file_to_image(game->mlx, game->conf->texture[3].path, &game->conf->o->width, &game->conf->o->height);
    if (!game->texture_img[0] || !game->texture_img[1] || !game->texture_img[2] ||
        !game->texture_img[3])
        err_msg("Failed to load textures");
    game->conf->o->texture_addr[0] = (unsigned int *)mlx_get_data_addr(
        game->texture_img[0], &game->conf->o->texture_bpp[0], &game->conf->o->texture_ll[0], &game->conf->o->texture_endian[0]);
    game->conf->o->texture_addr[1] = (unsigned int *)mlx_get_data_addr(
        game->texture_img[1], &game->conf->o->texture_bpp[1], &game->conf->o->texture_ll[1], &game->conf->o->texture_endian[1]);
    game->conf->o->texture_addr[2] = (unsigned int *)mlx_get_data_addr(
        game->texture_img[2], &game->conf->o->texture_bpp[2], &game->conf->o->texture_ll[2], &game->conf->o->texture_endian[2]);
    game->conf->o->texture_addr[3] = (unsigned int *)mlx_get_data_addr(
        game->texture_img[3], &game->conf->o->texture_bpp[3], &game->conf->o->texture_ll[3], &game->conf->o->texture_endian[3]);
    if (!game->conf->o->texture_addr[0] || !game->conf->o->texture_addr[1] ||
        !game->conf->o->texture_addr[2] || !game->conf->o->texture_addr[3])
        err_msg("Failed to get texture address");
}

void parse_func(char *file, t_build *b, t_data *data)
{
    int fd = open(file, O_RDONLY);
    if (fd < 1)
        err_msg("Failed to open file");
    char *line = get_next_line(fd);
    while (line != NULL)
    {
        if (data->is_last == 2 && *line != '\n')
        {
            char *is_line;
            is_line = add_map_line(b, line, data, &fd);
            if (data->is_last == 3)
            {
                char *trimmed = ft_trim(is_line);
                while (trimmed != NULL && *trimmed == '\n')
                    trimmed = ft_trim(get_next_line(fd));
                if (trimmed != NULL)
                    err_msg("New line detected in map");
                else
                    break;
            }
            line = is_line;
        }
        else if (*line != '\n')
        {
            ft_parse_tandc(line, data);
            line = get_next_line(fd);
        }
        else
            line = get_next_line(fd);
    }
}

void isnot_wall(my_game *game, double x, double y)
{
    if (game->conf->map[(int)y][(int)x] != '\0' && game->conf->map[(int)y][(int)x] != '1')
    {
        game->player_x = x;
        game->player_y = y;
    }
    else
        return;   
}

void    handle_esc(my_game *game)
{
    mlx_destroy_image(game->mlx, game->img->img_ptr);
    mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit (1);
}

int handle_keypress(int kc, my_game *game) 
{
    double move_speed = 0.1;
    double rot_speed = 0.05;

    if (kc == ESC_KEY)
		handle_esc(game);
    if (kc == W_KEY)
    {
        double new_x = game->player_x + game->player_dir_x * move_speed;
        double new_y = game->player_y + game->player_dir_y * move_speed;
        isnot_wall(game, new_x, new_y);
    } 
    else if (kc == S_KEY)
    {
        double new_x = game->player_x - game->player_dir_x * move_speed;
        double new_y = game->player_y - game->player_dir_y * move_speed;
        isnot_wall(game, new_x, new_y);
    }
    else if (kc == A_KEY)
    {
        double new_x = game->player_x + game->player_dir_y * move_speed;
        double new_y = game->player_y - game->player_dir_x * move_speed;
        isnot_wall(game, new_x, new_y);
        }
    else if (kc == D_KEY)
    {
        double new_x = game->player_x - game->player_dir_y * move_speed;
        double new_y = game->player_y + game->player_dir_x * move_speed;
        isnot_wall(game, new_x, new_y);        
    }
    else if (kc == RIGHT_ARROW)
    {
        //for direction vector
        double old_dir_x = game->player_dir_x;
        game->player_dir_x = game->player_dir_x * cos(rot_speed) - game->player_dir_y * sin(rot_speed);
        game->player_dir_y = old_dir_x * sin(rot_speed) + game->player_dir_y * cos(rot_speed);
        //for camera plane
        double old_plane_x = game->plane_x;
        game->plane_x = game->plane_x * cos(rot_speed) - game->plane_y * sin(rot_speed);
        game->plane_y = old_plane_x * sin(rot_speed) + game->plane_y * cos(-rot_speed);
    }
    else if (kc == LEFT_ARROW)
    {
        double old_dir_x = game->player_dir_x;
        game->player_dir_x = game->player_dir_x * cos(-rot_speed) - game->player_dir_y * sin(-rot_speed);
        game->player_dir_y = old_dir_x * sin(-rot_speed) + game->player_dir_y * cos(-rot_speed);

        double old_plane_x = game->plane_x;
        game->plane_x = game->plane_x * cos(-rot_speed) - game->plane_y * sin(-rot_speed);
        game->plane_y = old_plane_x * sin(-rot_speed) + game->plane_y * cos(-rot_speed);
    }
    clear_image(game->img);
    render_map(game); // Redraw the scene
    mlx_put_image_to_window(game->mlx, game->win, game->img->img_ptr, 0, 0);
    // clear_image(game->img);
    return 0;
}


int main(int argc, char **argv)
{
    if (argc != 2)
        err_msg("only two args");
    t_build b;
    t_data data;
    b.count = 0;
    data.is_last = 0;
    ft_ext_check(argv[1], ".cub");
    parse_func(argv[1], &b, &data);
    int i = 0;
    if (b.map_lines[i] == NULL) // is this supposed to be while loop??
        err_msg("Error");
    
    ft_validate_textures(&data);
    process_map(&b, &data);

    // testing parsing start
    //printing_shit(&b, &data);
    // testing parsing end

    my_game game;
    t_img   img;
    t_press ks;
    t_texture_object ob;
    game.img = &img;
    game.conf = &data;
    game.conf->o = &ob;

    game.keys = ft_init_keys(&ks);
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
    (game.img)->img_ptr = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    (game.img)->addr = mlx_get_data_addr(game.img->img_ptr, &game.img->bbp, &game.img->line_length,
		&game.img->endian);
    game.player_x = (double)data.num[1] + 0.5;
    game.player_y = (double)data.num[0] + 0.5;
    ft_player_orientation(&game);
    //clear_image(game.img);
    mlx_texture_load(&game);
    render_map(&game);
    mlx_put_image_to_window(game.mlx, game.win, img.img_ptr, 0, 0);
    mlx_hook(game.win, 2, 1L<<0, ft_on_press, &game.keys);
    mlx_hook(game.win, 3, 1L<<1, ft_on_release, &game.keys);
    mlx_key_hook(game.win, handle_keypress, &game);
	mlx_loop(game.mlx);
    // where do we clear image, window?
    return EXIT_SUCCESS;
}
