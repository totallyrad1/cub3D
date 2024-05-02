/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:33:28 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/02 20:53:12 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void	hinter(t_data *data, double *xinter, double *yinter, double angle)
{
	(*yinter) = ((int)data->y / TILE_SIZE) * TILE_SIZE + !data->up * TILE_SIZE;
	(*xinter) = (int)data->x + ((*yinter) - (int)data->y) / tan(angle);
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

int	is_wall(t_data *data, double xx, double yy)
{
	int	x;
	int	y;

	x = xx / TILE_SIZE;
	y = yy / TILE_SIZE;
	if (x <= 0 || x >= (data->j / TILE_SIZE)
		|| y <= 0 || y >= (data->i) / TILE_SIZE)
		return (1);
	if (data->mp[x][y] == '1')
		return (1);	
	if (data->mp[x][y] == 'D')
	{
		if (x == (int)(data->y / TILE_SIZE)
			|| x == (int)(data->y / TILE_SIZE) + 1
			|| x == (int)(data->y / TILE_SIZE) - 1)
		{
			if (y == (int)(data->x / TILE_SIZE)
				|| y == (int)(data->x / TILE_SIZE) - 1
				|| y == (int)(data->x / TILE_SIZE) + 1)
				return (0);
		}
		return (2);
	}
	return (0);
}

double	hcast(t_data *data, double angle, double xstep, double ystep)
{
	double	xinter;
	double	yinter;
	int		m;

	direction(angle, &data->up, &data->right);
	hinter(data, &xinter, &yinter, angle);
	hstep(data, &xstep, &ystep, angle);
	while (xinter > 0 && xinter < data->i && yinter > 0 && yinter < data->j)
	{
		m = is_wall(data, yinter, xinter);
		if (m)
		{
			data->hhitx = xinter;
			data->hhity = yinter + data->up;
			if (m == 2)
				data->hdoor = 1;
			else
				data->hdoor = 0;
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
	int		m;

	direction(angle, &data->up, &data->right);
	vinter(data, &xinter, &yinter, angle);
	vstep(data, &xstep, &ystep, angle);
	while (xinter > 0 && xinter < data->i && yinter > 0 && yinter < data->j)
	{
		m = is_wall(data, yinter, xinter);
		if (m)
		{
			data->vhitx = xinter + !data->right;
			data->vhity = yinter;
			if (m == 2)
				data->vdoor = 1;
			else
				data->vdoor = 0;
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
