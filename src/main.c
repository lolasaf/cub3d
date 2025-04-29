/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:18:24 by kforfoli          #+#    #+#             */
/*   Updated: 2025/04/29 20:54:43 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_print(char **map)
{
    int i = 0;
    while(map[i] != NULL)
    {
        printf("%s\n", map[i]);
        i++;
    }
}

int main(int argc, char **argv)
{
    // SANDY'S MAIN START
    if (argc != 2)
        err_msg("only two args");
    t_build b;
    t_data data;
    b.count = 0;
    data.is_last = 0;
    ft_ext_check(argv[1], ".cub");

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        err_msg("Failed to open file");
    char *line = get_next_line(fd);
    while (line != NULL)
    {
        if (data.is_last == 2)
        {
            // if (((strchr(line, '0') != NULL || strchr(line, '1') != NULL)) && *line != '\n')
            //         add_map_line(&b, line, &data);
            add_map_line(&b, line, &data);
            if (data.is_last == 3)
                err_msg("New line detected in map");
        }
        else if (*line != '\n')
            ft_parse_tandc(line, &data);
        line = get_next_line(fd);
    }

    int i = 0;
    if (b.map_lines[i] == NULL)
        err_msg("Error");
    while(b.map_lines[i])
    {
        printf("%s\n", b.map_lines[i]);
        i++;
    }
    i = 0;
    while(i < 4)
    {
        printf("%s\n", data.texture[i].identifier);
        printf("%s\n", data.texture[i].path);
        i++;
    }
    process_map(&b, &data); 
    printf("\n\n");
    ft_print(data.map); 

    // SANDY'S MAIN END

    // testing parsing start

    printf("Textures:\n");
    printf("NO: %s\n", data.texture[0].path);
    printf("SO: %s\n", data.texture[1].path);
    printf("WE: %s\n", data.texture[2].path);
    printf("EA: %s\n", data.texture[3].path);
    printf("Floor color: %d, %d, %d\n", data.color[0].rgb[0], data.color[0].rgb[1], data.color[0].rgb[2]);
    printf("Ceiling color: %d, %d, %d\n", data.color[1].rgb[0], data.color[1].rgb[1], data.color[1].rgb[2]);
    printf("Map (%d lines):\n", data.map_width);
    i = 0;
    while(data.map[i])
    {
        printf("%s\n", data.map[i++]);
    }
    // printf("id: %c\n path: %d\n", data.color[0].type);
    // while ()
    // printf("id: %c\n path: %d\n", data.color[1].type, data.color[1].rgb[1]);
    // printf("Height: %d\n", data.map_height);
    // printf("Height: %d\n", data.map_width);
    
    // testing parsing end

    // Lola codes ... start
    //draw_minimap(&data);
    my_game game;
    t_img   img;
    game.img = &img;
    game.conf = &data;
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
    (game.img)->img_ptr = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    (game.img)->addr = mlx_get_data_addr(game.img->img_ptr, &game.img->bbp, &game.img->line_length,
		&game.img->endian);
    game.player_x = 4;
    game.player_y = 2.5;
    game.player_dir_x = 1.0;
    game.player_dir_y = 0.0;
    game.plane_x = 0.0;
    game.plane_y = 0.66;
    game.conf->map_width = game.conf->map_height;
    render_map(&game);
    mlx_put_image_to_window(game.mlx, game.win, img.img_ptr, 0, 0);
	mlx_loop(game.mlx);
    // LOLA"S CODE ENDS HERE
    
    return EXIT_SUCCESS;
}