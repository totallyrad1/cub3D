/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:33:28 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/09 15:39:16 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	hinter(t_data *data, double *xinter, double *yinter, double angle)
{
	(*yinter) = ((int)(data->y) / TILE_SIZE) * TILE_SIZE + !data->up * TILE_SIZE;
	(*xinter) = (int)(data->x) + ((*yinter) - (int)(data->y)) / tan(angle);
	(*yinter) += -data->up;
}

void	hstep(t_data *data, double *xstep, double *ystep, double angle)
{
	data->hhitx = INT_MAX;
	(*ystep) = TILE_SIZE;
	if (data->up)
		(*ystep) *= -1;
	(*xstep) = TILE_SIZE / tan(angle);
	if (!data->right && (*xstep) > 0)
		(*xstep) *= -1;
	if (data->right && (*xstep) < 0)
		(*xstep) *= -1;
}

int	is_wall(t_data *data, int x, int y)
{
	if (x <= 0 || x >= (data->j / TILE_SIZE)
		|| y <= 0 || y >= (data->i) / TILE_SIZE)
		return (1);
	if (data->mp[x][y] == '1')
		return (1);
	return (0);
}

double	hcast(t_data *data, double angle, double xstep, double ystep)
{
	double	xinter;
	double	yinter;

	direction(angle, &data->up, &data->right);
	hinter(data, &xinter, &yinter, angle);
	hstep(data, &xstep, &ystep, angle);
	while (xinter > 0 && xinter < data->i && yinter > 0 && yinter < data->j)
	{
		if (is_wall(data, (yinter / TILE_SIZE), (xinter / TILE_SIZE)))
		{
			data->hhitx = xinter;
			data->hhity = yinter + data->up;
			break ;
		}
		else
		{
			xinter += xstep;
			yinter += ystep;
		}
	}
	if (data->hhitx == INT_MAX)
		return (INT_MAX);
	return (dis(data->x, data->y, data->hhitx, data->hhity));
}

double	vcast(t_data *data, double angle, double xstep, double ystep)
{
	double	xinter;
	double	yinter;

	direction(angle, &data->up, &data->right);
	vinter(data, &xinter, &yinter, angle);
	vstep(data, &xstep, &ystep, angle);
	while (xinter > 0 && xinter < data->i && yinter > 0 && yinter < data->j)
	{	
		if (is_wall(data, (yinter / TILE_SIZE), (xinter / TILE_SIZE)))
		{
			data->vhitx = xinter + !data->right;
			data->vhity = yinter;
			break ;
		}
		else
		{
			xinter += xstep;
			yinter += ystep;
		}
	}
	if (data->vhitx == INT_MAX)
		return (INT_MAX);
	return (dis(data->x, data->y, data->vhitx, data->vhity));
}

double	cast(t_data *data, double angle)
{
	double	h;
	double	v;

	h = hcast(data, angle, 0, 0);
	v = vcast(data, angle, 0, 0);
	if (h > v)
	{
		data->ver = 1;
		data->hhitx = data->vhitx;
		data->hhity = data->vhity;
		return (v);
	}
	data->ver = 0;
	return (h);
}
