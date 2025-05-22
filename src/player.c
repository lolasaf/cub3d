#include "../inc/cub3d.h"

t_press* ft_init_keys(t_press *k)
{
    k->key_up = false;
    k->key_down = false;
    k->key_left = false;
    k->key_right = false;
    k->rotate_l = false;
    k->rotate_r = false;
    return k;
}

void    ft_player_orientation(my_game *g)
{
    if (g->conf->player == 'N')
    {
        g->player_dir_x = 0;
        g->player_dir_y = 1;
        g->plane_x = -0.66;
        g->plane_y = 0.0;
    }
    else if (g->conf->player == 'S')
    {
        g->player_dir_x = 0;
        g->player_dir_y = -1;
        g->plane_x = 0.66;
        g->plane_y = 0.0;
    }
    else if (g->conf->player == 'E')
    {
        g->player_dir_x = 1;
        g->player_dir_y = 0;
        g->plane_x = 0.0;
        g->plane_y = 0.66;
    }
    else if (g->conf->player == 'W')
    {
        g->player_dir_x = -1;
        g->player_dir_y = 0;
        g->plane_x = 0.0;
        g->plane_y = -0.66;
    }
}

int ft_on_press(int kc, my_game *g)
{
    // if ((t_img*)(g->texture_img[3]))
    //     printf("BEFORE ft_on_press 3 img->image = %p\n", ((t_img*)(g->texture_img[3]))->image);
    // else
    //     write(1, "BLA\n", 4);
    if(kc == 119)  //W A:97 S:115 D:100 LEFT:65361 Right: 65363
        g->keys->key_up = true;
    else if (kc == 115)
        g->keys->key_down = true;
    else if (kc == 97)
        g->keys->key_left = true;
    else if (kc == 100)
        g->keys->key_right = true;
    else if (kc == 65361)
        g->keys->rotate_l = true;
    else if (kc == 65363)
        g->keys->rotate_r = true;
    // if ((t_img*)(g->texture_img[3]))
    //     printf("AFTER ft_on_press 3 img->image = %p\n", ((t_img*)(g->texture_img[3]))->image);
    // else
    //     write(1, "BLA2\n", 5);
    return 0;
}

int ft_on_release(int kc, my_game *g)
{
    if ((t_img*)(g->texture_img[3]))
        printf("BEFORE ft_on_release 3 img->image = %p\n", ((t_img*)(g->texture_img[3]))->image);
    else
        write(1, "BLA3\n", 5);
    if(kc == 119)  //W A:97 S:115 D:100 LEFT:65361 Right: 65363
        g->keys->key_up = false;
    else if (kc == 115)
        g->keys->key_down = false;
    else if (kc == 97)
        g->keys->key_left = false;
    else if (kc == 100)
        g->keys->key_right = false;
    else if (kc == 65361)
        g->keys->rotate_l = false;
    else if (kc == 65363)
        g->keys->rotate_r = false;
    if ((t_img*)(g->texture_img[3]))
        printf("AFTER ft_on_release 3 img->image = %p\n", ((t_img*)(g->texture_img[3]))->image);
    else
        write(1, "BLA4\n", 5);
    return 0;
}
