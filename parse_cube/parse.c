/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include "cube.h"

void trim(char *str)
{
    char *start = str;
    char *end;
    
    while(*start && isspace((unsigned char)*start))
        start++;
    
    if (start != str)
        memmove(str, start, strlen(start) + 1);
    end = str + strlen(str) - 1;
    while(end >= str && isspace((unsigned char)*end))
        *end-- = '\0';
}

void    ft_parse_texture(char *line, t_type type, t_config *config)
{
    char *path = line + 2;
    while(*path && isspace((unsigned char)*path))
        path++;
    char *end = path;
    while(*end && !isspace((unsigned char)*end))
        end++;
    size_t len = end - path;
    char *texture_path = malloc(len + 1);
    if (!texture_path)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    strncpy(texture_path, path, len);
    texture_path[len] = '\0';
    if (type == NO_TEXTURE)
        config->textures[0] = texture_path;
    else if (type == SO_TEXTURE)
        config->textures[1] = texture_path;
    else if (type == WE_TEXTURE)
        config->textures[2] = texture_path;
    else if (type == EA_TEXTURE)
        config->textures[3] = texture_path;
}

void ft_parse_color(char *line, t_type type, t_config *config)
{
    char *ptr = line + 1;
    while (*ptr && isspace((unsigned char)*ptr))
        ptr++;
    int color[3];
    for(int i = 0; i < 3; i++)
    {
        color[i] = atoi(ptr);
        while(*ptr && *ptr != ',')
            ptr++;
        if (*ptr == ',')
            ptr++;
    }
    if (type == FLOOR_COLOR)
    {
        for (int i = 0; i < 3; i++)
            config->floor_color[i] = color[i];
    }
    else if(type == CEILING_COLOR)
    {
        for(int i = 0; i < 3; i++)
            config->ceiling_color[i] = color[i];
    }
}

void add_map_line(char *line, t_config *config)
{
    trim(line);
    config->map_lines++;
    config->map = realloc(config->map, sizeof(char*) * config->map_lines);
    if (!config->map)
    {
        perror("realloc failed");
        exit(EXIT_FAILURE);
    }
    config->map[config->map_lines - 1] = strdup(line);
    if (!config->map[config->map_lines - 1])
    {
        perror("strdup failed");
        exit(EXIT_FAILURE);
    }
}

// void    validate_config(t_config *config)
// {
//     for (int i = 0; i < 4; i++)
//     {
//         if (config->textures[i] == NULL)
//         {
//             fprintf(stderr, "Error: Missing texture for index %d\n", i);
//             exit(EXIT_FAILURE);
//         }
//     }
//     if (config->map_lines == 0)
//     {
//         fprintf(stderr, "Error: No map data found.\n");
//         exit(EXIT_FAILURE);
//     }
// }

void    parse_file(const char *filename, t_config *config)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    
    char *line = get_next_line(fd);
    while(line != NULL)
    {
        trim(line);
        if (line[0] == '\0')
        {
            free(line);
            line = get_next_line(fd);
            continue;
        }
        if (strncmp(line, "NO", 2) == 0)
            ft_parse_texture(line, NO_TEXTURE, config);
        else if (strncmp(line, "SO", 2) == 0)
            ft_parse_texture(line, SO_TEXTURE, config);
        else if (strncmp(line, "WE", 2) == 0)
            ft_parse_texture(line, WE_TEXTURE, config);
        else if (strncmp(line, "EA", 2) == 0)
            ft_parse_texture(line, EA_TEXTURE, config);
        else if (line[0] == 'F')
            ft_parse_color(line, FLOOR_COLOR, config);
        else if (line[0] == 'C')
            ft_parse_color(line, CEILING_COLOR, config);
        else
            add_map_line(line, config);
        
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    validate_config(config); //one in map_validation
}



int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <cub_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    t_config config = {0};
    config.map = NULL;
    config.map_lines = 0;
    parse_file(argv[1], &config);
    
    printf("Textures:\n");
    printf("NO: %s\n", config.textures[0]);
    printf("SO: %s\n", config.textures[1]);
    printf("WE: %s\n", config.textures[2]);
    printf("EA: %s\n", config.textures[3]);
    printf("Floor color: %d, %d, %d\n", config.floor_color[0], config.floor_color[1], config.floor_color[2]);
    printf("Ceiling color: %d, %d, %d\n", config.ceiling_color[0], config.ceiling_color[1], config.ceiling_color[2]);
    printf("Map (%d lines):\n", config.map_lines);
    for(int i = 0; i < config.map_lines; i++)
    {
        printf("%s\n", config.map[i]);
        free(config.map[i]);
    }
    free(config.map);
    for (int i = 0; i < 4; i++)
        free(config.textures[i]);
    return EXIT_SUCCESS;
}