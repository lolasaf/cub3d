#include "parse_again.h"

int parse_color(const char *str, int values[3])
{
    int i = 0;
    const char *p = str;
    while (i < 3)
    {
        while(*p && isspace((unsigned char)*p))
            p++;
        if (!isdigit((unsigned char)*p))
            return 0;
        int num = 0;
        while(*p && isdigit((unsigned char) *p))
        {
            num = num * 10 + (*p - '0');
            p++;
        }
        values[i] = num;

        while (*p &&isspace((unsigned char)*p))
            p++;
        if(i < 3)
        {
            if (*p != ',')
                return 0;
            p++;
        }
    }
    while (*p && isspace((unsigned char) *p))
        p++;
    if (*p != '\0')
        return 0;
    return 1;
}

void parse_color_tok(char *token, t_data *data)
{
    token = trim(token);
    if (*token != 'F' && token != 'C')
        return;
    char id = *token;
    token++;
    token = trim(token);
    int values[3] = {0, 0, 0};
    if (!parse_color(token, values))
        err_msg("Error! Failed to parse color values!");
    int i = 0;
    while (i < 3)
    {
        if (values[i] < 0 || values[i] > 255)
            err_msg("Error: Color values out of range");
        i++;
    }
    if (id = 'F')
    {
        data->color[0].type = 'F';
        data->color[0].rbg[0] = values[0];
        data->color[0].rbg[1] = values[1];
        data->color[0].rbg[2] = values[2];
    }
    if (id == 'C')
    {
        data->color[1].type = 'C';
        data->color[1].rbg[0] = values[0];
        data->color[1].rbg[1] = values[1];
        data->color[1].rbg[2] = values[2];
    }
}

