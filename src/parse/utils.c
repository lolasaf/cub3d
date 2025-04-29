#include "parse_again.h"

void ft_print(char **map)
{
    int i = 0;
    while(map[i] != NULL)
    {
        printf("%s\n", map[i]);
        i++;
    }
}