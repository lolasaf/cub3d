/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xtra.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:05:59 by kforfoli          #+#    #+#             */
/*   Updated: 2025/06/01 23:06:11 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_switch(int argc, char **argv, t_data *data)
{
	if (argc > 3 || argc == 1)
		err_msg("Only two/three args allowed!", NULL, NULL);
	if (argc == 3)
	{
		if (ft_strlen(argv[2]) != 1)
			err_msg("Please provide Y or N", NULL, NULL);
		if (argv[2][0] != 'Y' && argv[2][0] != 'N')
			err_msg("Third arguement that was provided should be either Y or N",
				NULL, NULL);
		if (argv[2][0] == 'Y')
			data->sprites = 1;
		else
			data->sprites = 0;
	}
	return ;
}

int	scale_color(int color, double factor)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color >> 16) & 0xFF) * factor);
	g = (int)(((color >> 8) & 0xFF) * factor);
	b = (int)((color & 0xFF) * factor);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

void	assign_texture(t_ray *ray, t_draw *draw_vars)
{
	if (ray->side == HORIZONTAL)
	{
		if (ray->dir_y > 0)
			draw_vars->texture = TEX_SOUTH;
		else
			draw_vars->texture = TEX_NORTH;
	}
	else
	{
		if (ray->dir_x > 0)
			draw_vars->texture = TEX_WEST;
		else
			draw_vars->texture = TEX_EAST;
	}
}
