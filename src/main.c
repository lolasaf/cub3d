/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:18:24 by kforfoli          #+#    #+#             */
/*   Updated: 2025/05/24 19:12:08 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void load_texture_img(my_game *game)
{
    game->texture_img[0] =
        mlx_xpm_file_to_image(game->mlx, game->conf->texture[0].path, &game->conf->o->width, &game->conf->o->height);
    game->texture_img[1] =
        mlx_xpm_file_to_image(game->mlx, game->conf->texture[1].path, &game->conf->o->width, &game->conf->o->height);
    game->texture_img[2] =
        mlx_xpm_file_to_image(game->mlx, game->conf->texture[2].path, &game->conf->o->width, &game->conf->o->height);
    game->texture_img[3] =
        mlx_xpm_file_to_image(game->mlx, game->conf->texture[3].path, &game->conf->o->width, &game->conf->o->height);
    game->texture_img[4] = NULL;
    if (!game->texture_img[0] || !game->texture_img[1] || !game->texture_img[2] ||
        !game->texture_img[3])
        err_msg("Failed to load textures");
}
void set_dets(my_game *game)
{
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

void mlx_texture_load(my_game *game)
{
    load_texture_img(game);
    set_dets(game);
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
                {
                    free(is_line);
                    break;
                }
            }
            line = is_line;
        }
        else if (*line != '\n')
        {
            ft_parse_tandc(line, data);
            if (line)
                free(line);
            line = get_next_line(fd);
        }
        else
        {
            if (line)
                free(line);
            line = get_next_line(fd);
        }
    }
    close(fd);
}


int main(int argc, char **argv)
{
    if (argc != 2)
        err_msg("only two args");
    t_build b;
    t_data data;
    memset(&b, 0, sizeof(t_build));
    memset(&data, 0, sizeof(t_data));
    b.count = 0;
    data.is_last = 0;
    ft_ext_check(argv[1], ".cub");
    parse_func(argv[1], &b, &data);
    int i = 0;
    if (b.map_lines[i] == NULL) // is this supposed to be while loop??
        err_msg("Error");
    
    ft_validate_textures(&data);
    process_map(&b, &data);

    int j = 0;
    while (j < b.count && b.map_lines[j] != NULL)
        free(b.map_lines[j++]);
    // testing parsing start
    //printing_shit(&b, &data);
    // testing parsing end

    my_game game;
    t_imgp   img;
    t_press ks;
    t_texture_object ob;
    game.img = &img;
    game.conf = &data;
    game.conf->o = &ob;
    game.z_buffer = (double *)malloc(SCREEN_WIDTH * sizeof(double));
    if (!game.z_buffer) err_msg("Failed to allocate z buff");
    // memset(&img, 0 , sizeof(t_img));
    // memset(&ob, 0, sizeof(t_texture_object));
    game.keys = ft_init_keys(&ks);
    game.mlx = mlx_init();
    if (!game.mlx) err_msg("Failed to initialize mlx");
    game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
    (game.img)->img_ptr = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!game.img->img_ptr) err_msg("Failed to create main img");
    (game.img)->addr = mlx_get_data_addr(game.img->img_ptr, &game.img->bbp, &game.img->line_length,
		&game.img->endian);
	if (!game.img->addr) err_msg("Failed to get address");
    game.player_x = (double)data.num[1] + 0.5;
    game.player_y = (double)data.num[0] + 0.5;
    ft_player_orientation(&game);
    //clear_image(game.img);
    mlx_texture_load(&game);
    mlx_sprite_load(&game);
    render_map(&game);

    mlx_hook(game.win, 2, 1, ft_on_press, &game);
    mlx_hook(game.win, 3, 2, ft_on_release, &game);
    mlx_key_hook(game.win, handle_keypress, &game);
    mlx_loop(game.mlx);
    exit(EXIT_SUCCESS);
}
