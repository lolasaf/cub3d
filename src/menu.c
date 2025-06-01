/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 01:19:01 by kforfoli          #+#    #+#             */
/*   Updated: 2025/06/01 21:01:18 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_menu(void)
{
	printf("\033[36m");
	printf("\n\n");
	printf(" ██▓███   ▒█████   ██ ▄█▀ ██▓   ▄▄▄█████▓ ██▓ ███▄ ▄███▓▓█████ ");
	printf("\n");
	printf("▓██░  ██▒▒██▒  ██▒ ██▄█▒ ▓██▒   ▓  ██▒ ▓▒▓██▒▓██▒▀█▀ ██▒▓█   ▀");
	printf("\n");
	printf("▓██░ ██▓▒▒██░  ██▒▓███▄░ ▒██▒   ▒ ▓██░ ▒░▒██▒▓██    ▓██░▒███   ");
	printf("\n");
	printf("▒██▄█▓▒ ▒▒██   ██░▓██ █▄ ░██░   ░ ▓██▓ ░ ░██░▒██    ▒██ ▒▓█  ▄ ");
	printf("\n");
	printf("▒██▒ ░  ░░ ████▓▒░▒██▒ █▄░██░     ▒██▒ ░ ░██░▒██▒   ░██▒░▒████▒");
	printf("\n");
	printf("▒▓▒░ ░  ░░ ▒░▒░▒░ ▒ ▒▒ ▓▒░▓       ▒ ░░   ░▓  ░ ▒░   ░  ░░░ ▒░ ░");
	printf("\n");
	printf("░▒ ░       ░ ▒ ▒░ ░ ░▒ ▒░ ▒ ░       ░     ▒ ░░  ░      ░ ░ ░  ░");
	printf("\n");
	printf("░░       ░ ░ ░ ▒  ░ ░░ ░  ▒ ░     ░       ▒ ░░      ░      ░   ");
	printf("\n");
	printf("             ░ ░  ░  ░    ░               ░         ░      ░  ░");
	printf("\n");
	printf("\n\n");
	printf("\033[0m");
}

void	print_poki(t_game *game)
{
	static int	collected = 0;

	collected++;
	printf("\033[35m");
	printf("++++-+-+-+-+-+-+-+-+-+ +--+ +-+-+-+-+-+ ++ +-+-+-+-+-+ +--++++\n");
	printf("+++|C|o|l|l|e|c|t|e|d| |%02d| |P|o|k|i|s| || |L|e|f|t|:| ",
		collected);
	printf("|%02d|+++\n", game->num_sprites - collected);
	printf("++++-+-+-+-+-+-+-+-+-+ +--+ + +-+-+-+-+ ++ +-+-+-+-+-+ +--++++\n");
	printf("\033[0m");
}

void	print_done(void)
{
	printf("\033[32m");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf(" ┓┏      ┏┓  ┓┓       ┓   ┓        ┏┓┓ ┓ ╻  ┏┓     ┓  ┏┳┏┓┳┓╻\n");
	printf(" ┗┫┏┓┓┏  ┃ ┏┓┃┃┏┓┏╋┏┓┏┫  ╋┣┓┏┓┏┳┓  ┣┫┃ ┃ ┃  ┃┓┏┓┏┓┏┫   ┃┃┃┣┫┃\n");
	printf(" ┗┛┗┛┗┻  ┗┛┗┛┗┗┗ ┗┗┗ ┗┻  ┗┛┗┗ ┛┗┗  ┛┗┗┛┗┛•  ┗┛┗┛┗┛┗┻  ┗┛┗┛┻┛•\n");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("\033[0m");
}

void	print_menu_err(void)
{
	printf("\033[31m");
	printf("\n\n");
	printf("▓█████  ██▀███   ██▀███   ▒█████   ██▀███  ");
	printf("\n");
	printf("▓█   ▀ ▓██ ▒ ██▒▓██ ▒ ██▒▒██▒  ██▒▓██ ▒ ██▒");
	printf("\n");
	printf("▒███   ▓██ ░▄█ ▒▓██ ░▄█ ▒▒██░  ██▒▓██ ░▄█ ▒");
	printf("\n");
	printf("▒▓█  ▄ ▒██▀▀█▄  ▒██▀▀█▄  ▒██   ██░▒██▀▀█▄  ");
	printf("\n");
	printf("░▒████▒░██▓"
		" ▒██▒░██▓ ▒██▒░ ████▓▒░░██▓ ▒██▒");
	printf("\n");
	printf("░░ ▒░ ░░ ▒▓ ░▒▓░░ ▒▓ ░▒▓░░ ▒░▒░▒░ ░ ▒▓ ░▒▓░");
	printf("\n");
	printf("░ ░  ░  ░▒ ░ ▒░  ░▒ ░ ▒░  ░ ▒ ▒░   ░▒ ░ ▒░");
	printf("\n");
	printf("   ░     ░░   ░   ░░   ░ ░ ░ ░ ▒    ░░   ░ ");
	printf("\n");
	printf("   ░  ░   ░        ░         ░ ░     ░     ");
	printf("\n");
	printf("\n");
	printf("\033[0m");
}

void	sprite_switch(int argc, char **argv, t_data *data)
{
	if (argc > 3 && argc != 1)
		err_msg("Only two/three args allowed!", NULL, NULL);
	if (argc == 3)
	{
		if (ft_strlen(argv[2]) != 1)
			err_msg("Third arguement that was provided should be either 0 or 1",
				NULL, NULL);
		if ((ft_atoi(argv[2]) != 1) && (ft_atoi(argv[2]) != 0))
			err_msg("Third arguement that was provided should be either 0 or 1",
				NULL, NULL);
		if (ft_atoi(argv[2]) == 1)
			data->sprites = 1;
		else
			data->sprites = 0;
	}
	return ;
}
