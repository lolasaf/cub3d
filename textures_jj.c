#include "cub3d.h"

// void cast_ray(t_game *game, int col)
// {
//     t_ray ray;

//     // Calculate ray direction for this screen column
//     double camera_x = 2 * col / (double)SCREEN_WIDTH - 1; // x-coordinate in camera space (-1 to +1)
//     ray.dir_x = game->player_dir_x + game->plane_x * camera_x;
//     ray.dir_y = game->player_dir_y + game->plane_y * camera_x;

//     // Current position in map
//     ray.map_x = (int)game->player_x;
//     ray.map_y = (int)game->player_y;

//     // Length of ray from current position to next x or y-side
//     double side_dist_x;
//     double side_dist_y;

//     // Length of ray needed to travel one x or y-side
//     double delta_dist_x = (ray.dir_x == 0) ? 1e30 : fabs(1 / ray.dir_x);
//     double delta_dist_y = (ray.dir_y == 0) ? 1e30 : fabs(1 / ray.dir_y);

//     // Direction to step in x or y-direction (either +1 or -1)
//     ray.step_x = (ray.dir_x < 0) ? -1 : 1;
//     ray.step_y = (ray.dir_y < 0) ? -1 : 1;

//     // Calculate initial side distances
//     if (ray.dir_x < 0)
//         side_dist_x = (game->player_x - ray.map_x) * delta_dist_x;
//     else
//         side_dist_x = (ray.map_x + 1.0 - game->player_x) * delta_dist_x;

//     if (ray.dir_y < 0)
//         side_dist_y = (game->player_y - ray.map_y) * delta_dist_y;
//     else
//         side_dist_y = (ray.map_y + 1.0 - game->player_y) * delta_dist_y;

//     // Perform DDA
//     ray.hit = 0; // Was there a wall hit?
//     ray.side = 0; // Was a NS or EW wall hit?
//     while (ray.hit == 0)
//     {
//         // Jump to next map square, OR in x-direction, OR in y-direction
//         if (side_dist_x < side_dist_y)
//         {
//             side_dist_x += delta_dist_x;
//             ray.map_x += ray.step_x;
//             ray.side = 0; // Hit a vertical (EW) wall
//         }
//         else
//         {
//             side_dist_y += delta_dist_y;
//             ray.map_y += ray.step_y;
//             ray.side = 1; // Hit a horizontal (NS) wall
//         }

//         // Check if ray has hit a wall
//         if (ray.map_x >= 0 && ray.map_x < game->conf->map_width &&
//             ray.map_y >= 0 && ray.map_y < game->conf->map_height &&
//             game->conf->map[ray.map_y][ray.map_x] == '1')
//         {
//             ray.hit = 1;
//         }
//     }

//     // Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
//     if (ray.side == 0)
//         ray.perp_distance = (side_dist_x - delta_dist_x);
//     else
//         ray.perp_distance = (side_dist_y - delta_dist_y);

//     // Calculate height of line to draw on screen
//     int line_height = (int)(SCREEN_HEIGHT / ray.perp_distance);

//     // Calculate lowest and highest pixel to fill current stripe
//     int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
//     if (draw_start < 0)
//         draw_start = 0;
//     int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
//     if (draw_end >= SCREEN_HEIGHT)
//         draw_end = SCREEN_HEIGHT - 1;

//     // Determine which texture to use based on the side and direction of the hit
//     int texture_index = 0;
//     if (game->conf->texture[0].path && game->conf->texture[1].path &&
//         game->conf->texture[2].path && game->conf->texture[3].path)
//     {
//         if (ray.side == 1) // Horizontal wall
//         {
//             if (ray.step_y == -1) // North
//                 texture_index = 0;
//             else // South
//                 texture_index = 1;
//         }
//         else // Vertical wall
//         {
//             if (ray.step_x == -1) // West
//                 texture_index = 2;
//             else // East
//                 texture_index = 3;
//         }
//     }

//     // Calculate where on the texture the ray hit
//     double wall_x; // Where exactly the wall was hit
//     if (ray.side == 0)
//         wall_x = game->player_y + ray.perp_distance * ray.dir_y;
//     else
//         wall_x = game->player_x + ray.perp_distance * ray.dir_x;
//     wall_x -= floor(wall_x);

//     // x coordinate on the texture
//     int texture_x = (int)(wall_x * game->conf->o->width);
//     if (ray.side == 0 && ray.dir_x > 0)
//         texture_x = game->conf->o->width - texture_x - 1;
//     if (ray.side == 1 && ray.dir_y < 0)
//         texture_x = game->conf->o->width - texture_x - 1;

//     // Draw the vertical stripe with the correct texture pixel
//     for (int y = draw_start; y < draw_end; y++)
//     {
//         int texture_y = (((y * 256 - SCREEN_HEIGHT * 128 + line_height * 128) * game->conf->o->height) / line_height) / 256;
//         if (texture_y < 0)
//             texture_y = 0;
//         if (texture_y >= game->conf->o->height)
//             texture_y = game->conf->o->height - 1;

//         unsigned int color;
//         char *dst = game->conf->o->texture_addr[texture_index] + (texture_y * game->conf->o->texture_ll[texture_index] + texture_x * (game->conf->o->texture_bpp[texture_index] / 8));
//         color = *(unsigned int *)dst;

//         // Apply a slight darkening effect for north/east walls (optional)
//         if ((ray.side == 1 && ray.step_y == -1) || (ray.side == 0 && ray.step_x == 1))
//         {
//             color = (color >> 1) & 8355711; // Equivalent to color / 2 for RGB
//         }

//         put_pixel_to_img(game->mlx, game->img, col, y, color);
//     }
// }

#include "cub3d.h"

void cast_ray(t_game *game, int col)
{
    t_ray ray;

    // Calculate ray direction for this screen column
    double camera_x = 2 * col / (double)SCREEN_WIDTH - 1;
    ray.dir_x = game->player_dir_x + game->plane_x * camera_x;
    ray.dir_y = game->player_dir_y + game->plane_y * camera_x;

    // Current position in map
    ray.map_x = (int)game->player_x;
    ray.map_y = (int)game->player_y;

    // Length of ray from current position to next x or y-side
    double side_dist_x;
    double side_dist_y;

    // Length of ray needed to travel one x or y-side
    double delta_dist_x = (ray.dir_x == 0) ? 1e30 : fabs(1 / ray.dir_x);
    double delta_dist_y = (ray.dir_y == 0) ? 1e30 : fabs(1 / ray.dir_y);

    // Direction to step in x or y-direction (either +1 or -1)
    ray.step_x = (ray.dir_x < 0) ? -1 : 1;
    ray.step_y = (ray.dir_y < 0) ? -1 : 1;

    // Calculate initial side distances
    if (ray.dir_x < 0)
        side_dist_x = (game->player_x - ray.map_x) * delta_dist_x;
    else
        side_dist_x = (ray.map_x + 1.0 - game->player_x) * delta_dist_x;

    if (ray.dir_y < 0)
        side_dist_y = (game->player_y - ray.map_y) * delta_dist_y;
    else
        side_dist_y = (ray.map_y + 1.0 - game->player_y) * delta_dist_y;

    // Perform DDA
    ray.hit = 0;
    ray.side = 0;
    while (ray.hit == 0)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            ray.map_x += ray.step_x;
            ray.side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            ray.map_y += ray.step_y;
            ray.side = 1;
        }
        if (ray.map_x >= 0 && ray.map_x < game->conf->map_width &&
            ray.map_y >= 0 && ray.map_y < game->conf->map_height &&
            game->conf->map[ray.map_y][ray.map_x] == '1')
        {
            ray.hit = 1;
        }
    }

    // Calculate distance projected on camera direction
    if (ray.side == 0)
        ray.perp_distance = (side_dist_x - delta_dist_x);
    else
        ray.perp_distance = (side_dist_y - delta_dist_y);

    // Calculate height of line to draw on screen
    int line_height = (int)(SCREEN_HEIGHT / ray.perp_distance);

    // Calculate lowest and highest pixel to fill current stripe
    int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
    if (draw_start < 0)
        draw_start = 0;
    int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
    if (draw_end >= SCREEN_HEIGHT)
        draw_end = SCREEN_HEIGHT - 1;

    // Determine which texture to use
    int texture_index = 0;
    if (game->conf->texture[0].path && game->conf->texture[1].path &&
        game->conf->texture[2].path && game->conf->texture[3].path)
    {
        if (ray.side == 1)
        {
            if (ray.step_y == -1)
                texture_index = 0; // north
            else
                texture_index = 1; // south
        }
        else
        {
            if (ray.step_x == -1)
                texture_index = 2;
            else
                texture_index = 3;
        }
    }

    // Calculate where on the texture the ray hit
    double wall_x;
    if (ray.side == 0)
        wall_x = game->player_y + ray.perp_distance * ray.dir_y;
    else
        wall_x = game->player_x + ray.perp_distance * ray.dir_x;
    wall_x -= floor(wall_x);

    // x coordinate on the texture
    int texture_x = (int)(wall_x * game->conf->o->width);
    if (ray.side == 0 && ray.dir_x > 0)
        texture_x = game->conf->o->width - texture_x - 1;
    if (ray.side == 1 && ray.dir_y < 0)
        texture_x = game->conf->o->width - texture_x - 1;

    // Draw the vertical stripe with the correct texture pixel
    for (int y = draw_start; y < draw_end; y++)
    {
        int texture_y = (((y * 256 - SCREEN_HEIGHT * 128 + line_height * 128) * game->conf->o->height) / line_height) / 256;
        if (texture_y < 0)
            texture_y = 0;
        if (texture_y >= game->conf->o->height)
            texture_y = game->conf->o->height - 1;

        unsigned int color;
        char *dst = (char *)game->conf->o->texture_addr[texture_index] + (texture_y * game->conf->o->texture_ll[texture_index] + texture_x * (game->conf->o->texture_bpp[texture_index] / 8));
        color = *(unsigned int *)dst;

        // Apply a slight darkening effect for north/east walls (optional)
        if ((ray.side == 1 && ray.step_y == -1) || (ray.side == 0 && ray.step_x == 1))
            color = (color >> 1) & 8355711;

        put_pixel_to_img(game->mlx, game->img, col, y, color);
    }
}


void ft_render_map(t_game *game)
{
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        cast_ray(game, x);
    }
}

void    put_pixel_to_img(void *mlx, t_img *img, int x, int y, int color)
{
    (void)mlx;
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bbp / 8));
    *(unsigned int *)dst = color;
}