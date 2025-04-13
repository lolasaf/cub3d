#include "parse_again.h"

void ft_parse_tandc(const char *line, t_data *data)
{
    const char *p = line;
    while(*p)
    {
        while(*p && isspace((unsigned char)*p))
            p++;
        if (!*p)
            break;
        const char *token_start = p;
        while (*p && !isspace((unsigned char)*p))
            p++;
        int token_len = p - token_start;
        char *token = malloc(token_len + 1);
        if (!token)
            err_msg("Memory allocation failure");
        strncpy(token, token_start, token_len);
        token[token_len] = '\0';
        if (strncmp(token, "NO", 2) == 0 || strncmp(token, "SO", 2) == 0 || strncmp(token, "WE", 2) == 0 || strncmp(token, "EA", 2) == 0)
            ft_parse_texture(token, data);
        if (token[0] == 'F' || token[0] == 'C')
            parse_color_tok(token,data);
        free(token);
    }
}

























//textures

// int parse_texture(char *line, t_data *data)
// {
//     if (strncmp(line, "NO", 2) == 0)
//     {
//         data->texture[0].identifier = strdup("NO");
//         if (strchr(line, '.') && strchr(line + 1, '/'))
//             data->texture[0].path = strdup(strchr(line, '.'));
//     }
//     if (strcmp(line, "SO", 2) == 0)
//     {
//         data->texture[1].identifier = strdup("SO");
//         if (strchr(line, '.') && strchr(line + 1, '/'))
//             data->texture[1].path = strdup(strchr(line, '.'));
//     }
//     if (strncmp(line, "WE", 2) == 0)
//     {
//         data->texture[2].identifier = strdup("WE");
//         if (strchr(line, '.') && strchr(line + 1, '/'))
//             data->texture[2].path = strdup(strchr(line, '.'));
//     }
//     if (strncmp(line, "EA", 2) == 0)
//     {
//         data->texture[3].identifier = strdup("EA");
//         if (strchr(line, '.') && strchr(line + 1, '/'))
//             data->texture[3].path = strdup(strchr(line, '.'));
//     }
// }

// int parse_color(char *line, t_data *data)
// {
//     if (*line == 'F')
//     {
//         data->color->type = 'F';
        
//     }
// }

// t_data parse_data(char *line, t_data *data)
// {
//     if (*line == '1' && data->is_last != 0)
//         return parse_map();
//     if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
//         return parse_texture();
//     if (*line == 'F' || *line == 'C')
//         return parse_color();
//     else 
//         return err_msg();
// }

