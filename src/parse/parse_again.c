#include "parse_again.h"



void ft_parse_tandc(const char *line, t_data *data)
{
    const char *p = line;
    const char *another = line;
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
            ft_parse_texture((char *)another, data);
        if (token[0] == 'F' || token[0] == 'C')
            parse_color_tok((char *)another ,data);
        free(token);
    }
}

void add_map_line(t_build *assemble, const char *line)
{
    char *cpy = (char *)line;
    if (assemble->count >= MAX_LINES)
        err_msg("Too many lines");
    if (strchr(cpy, '\n') != NULL)
    {
        int distance = strchr(cpy, '\n') - cpy;
        cpy[distance] = '\0';
    }
    assemble->map_lines[assemble->count] = strdup(cpy);
    if (!assemble->map_lines[assemble->count])
        err_msg("Strdup failed");
    assemble->count++;
}

void ft_ext_check(const char *path, const char *cub)
{
    const char *base;
    const char *slash;
    const char *dot;

    slash = strrchr(path, '/');
    if (slash != NULL)
        base = slash + 1;
    else
        base = path;
    dot = strrchr(base, '.');
    if (dot == NULL)
        err_msg("ERR:Not a valid file extension");
    if (strcmp(dot, cub) != 0)
        err_msg("ERR: Not a valid file extension");

}

int main(int argc, char **argv)
{
    if (argc != 2)
        err_msg("only two args");
    else
    {
        t_build b;
        t_data data;
        b.count = 0;
        data.is_last = 0;
        ft_ext_check(argv[1], ".cub");
    
        int fd = open(argv[1], O_RDONLY);
        char *line = get_next_line(fd);
        while(line != NULL)
        {
            if (data.is_last == 2)
            {
                if ((strchr(line, '0') != NULL || strchr(line, '1') != NULL) && *line != '\n')
                        add_map_line(&b, line);
            }
            else if(*line != '\n')
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
        process_map(&b, &data); 
        printf("\n\n");
        ft_print(data.map); 
    }

}