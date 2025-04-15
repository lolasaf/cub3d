/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:11:24 by wel-safa          #+#    #+#             */
/*   Updated: 2025/04/12 14:09:47 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
pos = [x, y]
raydir = [dx, dy]
*/
float	*dda(float *pos, float *raydir)
{
	float	step;
	float	stepx;
	float	stepy;
	float	*hitpos;

	hitpos = (float *)malloc(sizeof(float) * 2);
	if (raydir[0] < 0) // dx < 0
	{
		stepx = (floorf(pos[0]) - pos[0]) / raydir[0];
	}
	else if (raydir[0] > 0) // dx > 0
	{
		stepx = (ceilf(pos[0]) - pos[0]) / raydir[0];
	}
	else // dx = 0
		stepx = INFINITY;
	
	if (raydir[1] < 0) // dy < 0
	{
		stepy = (floorf(pos[1]) - pos[1]) / raydir[1];
	}
	else if (raydir[1] > 0) // dy > 0
	{
		stepy = (ceilf(pos[1]) - pos[1]) / raydir[1];
	}
	else // dy = 0;
		stepy = INFINITY;
	
	hitpos[0] = pos[0] + raydir[0] * (fminf(stepx, stepy));
	hitpos[1] = pos[1] + raydir[1] * (fminf(stepx, stepy));
	
	return (hitpos); // returns malloced float pointer
}