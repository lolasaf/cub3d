#include "parse_again.h"

char *trim(char *line)
{
    while(isspace((unsigned char)*line))
        line++;
    if (*line == 0)
        return line;
    char *end = line + strlen(line) -1;
    while(end > line && isspace((unsigned char)*end))
        end--;
    *(end + 1) = '\0';
    return line;
}

int ft_parse_texture(char *line, t_data *data)
{
    char *trimmed = trim(line);
    if (strncmp(trimmed, "NO", 2) == 0)
    {
        data->texture[0].identifier = strdup("NO");
        char *ptr = line + 2;
        while (*ptr && isspace((unsigned char)*ptr))
            ptr++;
        if (!strchr(ptr, '/'))
            err_msg("Error: Invalid texture path");
        data->texture[0].path = strdup(ptr);
    }
    if (strncmp(line, "SO", 2) == 0)
    {
        data->texture[1].identifier = strdup("SO");
        char *ptr = line + 2;
        while (*ptr && isspace((unsigned char)*ptr))
            ptr++;
        if (!strchr(ptr, '/'))
            err_msg("Error: Invalid texture path");
        data->texture[1].path = strdup(ptr);
    }
    if (strncmp(line, "WE", 2) == 0)
    {
        data->texture[2].identifier = strdup("WE");
        char *ptr = line + 2;
        while (*ptr && isspace((unsigned char)*ptr))
            ptr++;
        if (!strchr(ptr, '/'))
            err_msg("Error: Invalid texture path");
        data->texture[2].path = strdup(ptr);
    }
    if (strncmp(line, "EA", 2) == 0)
    {
        data->texture[3].identifier = strdup("EA");
        char *ptr = line + 2;
        while (*ptr && isspace((unsigned char)*ptr))
            ptr++;
        if (!strchr(ptr, '/'))
            err_msg("Error: Invalid texture path");
        data->texture[3].path = strdup(ptr);
    }
}