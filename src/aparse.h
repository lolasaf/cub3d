#ifndef APARSE_H
# define APARSE_H

#include "inc/cub3d.h"
#include "parse_again.h"

typedef enum
{
    TEXTURE,
    COLOR,
    MAP
}type;

typedef struct t_token
{
    type t;
    union{
        s_texture text;
        s_color col;
        s_map map;
    }data;
}s_token;


#endif