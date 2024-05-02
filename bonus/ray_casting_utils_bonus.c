/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:33:55 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/02 18:25:28 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

double	normalize(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	angle += (angle < 0) * 2 * M_PI;
	return (angle);
}

double	dis(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	direction(double angle, int *up, int *right)
{
	if (angle > 0 && angle < M_PI)
		*up = 0;
	else
		*up = 1;
	if (angle >= M_PI_2 && angle < (3 * M_PI_2))
		*right = 0;
	else
		*right = 1;
}

void	vinter(t_data *data, double *xinter, double *yinter, double angle)
{
	(*xinter) = ((int)data->x / TILE_SIZE)
			* TILE_SIZE + data->right * TILE_SIZE;
	(*yinter) = (int)data->y + ((*xinter) - (int)data->x) * tan(angle);
	(*xinter) += -!data->right;
}

void	vstep(t_data *data, double *xstep, double *ystep, double angle)
{
	data->vhitx = INT_MAX;
	(*xstep) = TILE_SIZE;
	if (!data->right)
		(*xstep) *= -1;
	(*ystep) = TILE_SIZE * tan(angle);
	if (data->up && (*ystep) > 0)
		(*ystep) *= -1;
	if (!data->up && (*ystep) < 0)
		(*ystep) *= -1;
}
