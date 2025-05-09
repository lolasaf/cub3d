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

int ft_on_press(int kc, my_game *g)
{
    if(kc == 119)  //W A:97 S:115 D:100 LEFT:65361 Right: 65363
        g->keys->key_up = true;
    if (kc == 115)
        g->keys->key_down = true;
    if (kc == 97)
        g->keys->key_left = true;
    if (kc == 100)
        g->keys->key_right = true;
    if (kc == 65361)
        g->keys->rotate_l = true;
    if (kc == 65363)
        g->keys->rotate_r = true;
    return 0;
}

int ft_on_release(int kc, my_game *g)
{
    if(kc == 119)  //W A:97 S:115 D:100 LEFT:65361 Right: 65363
        g->keys->key_up = false;
    if (kc == 115)
        g->keys->key_down = false;
    if (kc == 97)
        g->keys->key_left = false;
    if (kc == 100)
        g->keys->key_right = false;
    if (kc == 65361)
        g->keys->rotate_l = false;
    if (kc == 65363)
        g->keys->rotate_r = false;
    return 0;
}