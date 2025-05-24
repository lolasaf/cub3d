#include "../inc/cub3d.h"

void ft_init_sprites(my_game *g)
{
  g->num_sprites = 2;

  int i;
  double b_x;
  double b_y;
  double s;

  i = 0;
  b_x = 2.5;
  b_y = 4.5;
  s = 3.0;
  while (i < g->num_sprites)
  {
    g->sprites[i].x = b_x + (i * s);
    g->sprites[i].y = b_y + (i * s);
    g->sprites[i].id = i;
    i++;
  }
}


void mlx_sprite_load(my_game *g)
{
  int i;
  int w;
  int h;

  const char *sprite_paths[MAX_SPRITES] = {
      "sprites/charizard.xpm",
      "sprites/mewtwo.xpm"
  };

  i = 0;
  while(i < MAX_SPRITES)
  {
    g->sprites[i].img = mlx_xpm_file_to_image(g->mlx, (char *)sprite_paths[i], &w, &h);
    if (!g->sprites[i].img)
        err_msg("Failed to load sprite texture. Check path!");//Potentially call freeing functions here as well check if they exist ie !null and then free
    i++;
  }

  ft_init_sprites(g);
}

void ft_sort(sprite_sort *to_sort, int count)
{
  int i;
  int j;
  sprite_sort temp;

  i = 0;
  while (i < count - 1)
  {
    j = i + 1;
    while (j < count)
    {
      if (to_sort[i].dist < to_sort[j].dist)
      {
        temp = to_sort[i];
        to_sort[i] = to_sort[j];
        to_sort[j] = temp;
      }
      j++;
    }
    i++;
  }
}

/*
void handle_sprites(my_game *g)
{
  sprite_sort to_sort[MAX_SPRITES];
  int         i;

  i = 0;
  while (i < game->num_sprites)
  {
    to_sort[i].dist = ((game->player_x - game->sprites[i].x) * (game->player_x - game->sprites[i].x)) +
                                  ((game->player_y - game->sprites[i].y) * (game->player_y - game->sprites[i].y));
    to_sort[i].index = i;
    i++;
  }
  ft_sort(to_sort, g->num_sprites);
  render_sprites(to_sort, g);
}
*/

void get_vertical_prop(t_sprite_props *prop)
{
  prop->s_h = (int)(SCREEN_HEIGHT / prop->t_y);
  prop->start_y = -prop->s_h / 2 + SCREEN_HEIGHT / 2;
  if (prop->start_y < 0)
      prop->start_y = 0;
  prop->end_y = prop->s_h / 2 + SCREEN_HEIGHT / 2;
  if (prop->end_y >= SCREEN_HEIGHT)
      prop->end_y = SCREEN_HEIGHT - 1;
}

void get_horizonatal_prop(t_sprite_props *prop)
{
  prop->s_w = (int)(SCREEN_HEIGHT / prop->t_y); // Often same as height for square sprites could also be tx 
  prop->start_x = -prop->s_w / 2 + prop->s_sx;
  if (prop->start_x < 0)
      prop->start_x = 0;
  prop->end_x = prop->s_w / 2 + prop->s_sx;
  if (prop->end_x >= SCREEN_WIDTH)
      prop->end_x = SCREEN_WIDTH - 1;
}

t_sprite_props calc_properties(my_game *g, t_sprite *s, double *catch)
{
  t_sprite_props prop;
  double x_rel;
  double y_rel;

  x_rel = s->x - g->player_x;
  y_rel = s->y - g->player_y;

  *catch = 1.0 / (g->plane_x * g->player_dir_y - g->player_dir_x * g->plane_y);
  if (fabs(*catch) < 1e-6)
    *catch = 1.0;
  prop.t_x = *catch * (g->player_dir_y * x_rel - g->player_dir_x * y_rel);
  prop.t_y = *catch * (-g->plane_y * x_rel + g->plane_x * y_rel);

  prop.s_sx = (int)((SCREEN_WIDTH / 2) * (1 + prop.t_x / prop.t_y));
  get_vertical_prop(&prop);
  get_horizonatal_prop(&prop);
  return prop;
}

unsigned int get_sprite_pixel_color(t_img *sprite_tex, int tex_x, int tex_y)
{
    unsigned int *tex_addr = (unsigned int *)sprite_tex->data;
    int tex_ll = sprite_tex->size_line;
    
    // Ensure tex_x and tex_y are within bounds (already done in calling functions, but good practice)
    if (tex_x < 0 || tex_x >= sprite_tex->width || tex_y < 0 || tex_y >= sprite_tex->height)
        return 0x0; // Return transparent/black if out of bounds

    return tex_addr[tex_y * (tex_ll / 4) + tex_x];
}

void draw_stripe(my_game *game, t_img *sprite_tex, t_sprite_props *prop, int stripe_x, int tex_x)
{
    int y = prop->start_y;
    int tex_y;
    unsigned int color;
    int d;

    while (y < prop->end_y)
    {
        // Calculate texture Y coordinate
        d = (y) * 256 - SCREEN_HEIGHT * 128 + prop->s_h * 128; //256 and 128 for fixed-point
        tex_y = ((d * sprite_tex->height) / prop->s_h) / 256;
        if (tex_y < 0) tex_y = 0;
        if (tex_y >= sprite_tex->height) tex_y = sprite_tex->height - 1;

        color = get_sprite_pixel_color(sprite_tex, tex_x, tex_y);
        
        // Basic transparency check: if color is black (0x000000), skip drawing
        if ((color & 0x00FFFFFF) != 0) // Check if RGB part is not zero
            put_pixel_to_img(game->mlx, game->img, stripe_x, y, color);
        y++;
    }
}

void single_sprite_render(my_game *g, t_img *sprite_tex, t_sprite_props *prop)
{   
  int stripe_x = prop->start_x;
  int tex_x;

  while (stripe_x < prop->end_x)
  {
    if (stripe_x >= 0 && stripe_x < SCREEN_WIDTH && prop->t_y < g->z_buffer[stripe_x])
    {
        tex_x = (int)(256 * (stripe_x - (-prop->s_w / 2 + prop->s_sx)) * sprite_tex->width / prop->s_w) / 256;
        if (tex_x < 0) tex_x = 0;
        if (tex_x >= sprite_tex->width) tex_x = sprite_tex->width - 1;
        draw_stripe(g, sprite_tex, prop, stripe_x, tex_x);
    }
    stripe_x++;
  }
}

void render_sprites(sprite_sort *to_sort, my_game *g)
{
  int i;
  t_sprite *s;
  t_img *sprite_tex;
  t_sprite_props prop;
  double catch;

  i = 0;
  while (i < g->num_sprites)
  {
    s = &g->sprites[to_sort[i].index];
    sprite_tex = (t_img *)g->sprites[s->id].img;
    if (!sprite_tex)
    {
      i++;
      continue;
      //orr err_msg?;
    }
    prop = calc_properties(g, s, &catch);
    if (prop.t_y <= 0.0 || prop.t_y < 0.01)
    {
      i++;
      continue;
    }
    single_sprite_render(g, sprite_tex, &prop);
    i++;
  }
}


void handle_sprites(my_game *g)
{
  sprite_sort to_sort[MAX_SPRITES];
  int         i;

  i = 0;
  while (i < g->num_sprites)
  {
    to_sort[i].dist = ((g->player_x - g->sprites[i].x) * (g->player_x - g->sprites[i].x)) +
                                  ((g->player_y - g->sprites[i].y) * (g->player_y - g->sprites[i].y));
    to_sort[i].index = i;
    i++;
  }
  ft_sort(to_sort, g->num_sprites);
  render_sprites(to_sort, g);
}
