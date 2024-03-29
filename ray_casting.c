#include "header.h"

double	normalize(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	angle += (angle < 0) * 2 * M_PI;
	return (angle);
}

int	dis(int x1, int y1, int x2, int y2)
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

double	hcast(t_data *data, double angle, double xstep, double ystep)
{
	int	up;
	int	right;
	double	xinter;
	double	yinter;

	data->hhitx = INT_MAX;
	direction(angle, &up, &right);
	yinter = (data->y / TILE_SIZE) * TILE_SIZE;
	yinter += !up * TILE_SIZE;
	xinter = data->x + (yinter - data->y) / tan(angle);
	ystep = TILE_SIZE;
	if (up)
		ystep *= -1;
	xstep = TILE_SIZE / tan(angle);
	if (!right && xstep > 0)
		xstep *= -1;
	if (right && xstep < 0)
		xstep *= -1;
	yinter += -up;
	while (xinter >= 0 && xinter < WIDTH && yinter >= 0 && yinter < HEIGHT)
	{
		if (data->mp[(int)floor(yinter / TILE_SIZE)][(int)floor(xinter / TILE_SIZE)] == '1')
		{
			data->hhitx = xinter;
			data->hhity = yinter + up;
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
	int	up;
	int	right;
	double	xinter;
	double	yinter;

	data->vhitx = INT_MAX;
	direction(angle, &up, &right);
	xinter = (data->x / TILE_SIZE) * TILE_SIZE;
	xinter += right * TILE_SIZE;

	yinter = data->y + (xinter - data->x) * tan(angle);

	xstep = TILE_SIZE;
	if (!right)
		xstep *= -1;

	ystep = TILE_SIZE * tan(angle);
	if (up && ystep > 0)
		ystep *= -1;
	if (!up && ystep < 0)
		ystep *= -1;
	xinter += -1 * !right;
	while (xinter >= 0 && xinter < WIDTH && yinter >= 0 && yinter < HEIGHT)
	{
		if (data->mp[(int)floor(yinter / TILE_SIZE)][(int)floor(xinter / TILE_SIZE)] == '1')
		{
			data->vhitx = xinter + 1 * !right;
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

int cast(t_data *data, double angle)
{
	double h;
	double v;

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