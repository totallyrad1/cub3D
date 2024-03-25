
#include "header.h"

double  normalizeangle(double angle)
{
	angle = fmod(angle, (M_PI * 2));
	if (angle < 0)
	  angle = angle + (M_PI * 2);
	return (angle);
}

void	direction_angle(int	*up, int *right, float angle)
{
	if (angle > 0 && angle <= M_PI)
		*up = 1;
	else
		*up = 0;
	if (angle > M_PI_2 && angle <= ((3 * M_PI) / 2))
		*right = 0;
	else 
		*right = 1;
}

int	h_cast(t_data *data, float angle, int xstep, int ystep)
{
	int	xinter;
	int	yinter;
	int	up;
	int	right;

	direction_angle(&up, &right, angle);
	data->hhitx = -1;
	xinter = (data->player.x / TILE_SIZE) * TILE_SIZE;
	xinter += TILE_SIZE * up;
	yinter = data->player.y + (xinter - data->player.x) / tan(data->player.angle);
	xstep = TILE_SIZE * !up * -2 + TILE_SIZE;
	ystep = TILE_SIZE / tan(data->player.angle);
	if (!right && ystep > 0)
		ystep *= -1;
	if (right && ystep < 0)
		ystep *= -1;
	xinter = xinter - 1 * !up;
	while (xinter >= 0 && xinter < WIDTH && yinter >= 0 && yinter < HEIGHT)
	{
		if (data->mp[xinter / TILE_SIZE][yinter / TILE_SIZE] == '1')
		{
			data->hhitx = xinter;
			data->hhity = yinter;
			break ;
		}
		else
		{
			xinter += xstep;
			yinter += ystep;
		}
	}
	return (0);
}

int	v_cast(t_data *data, float angle, int xstep, int ystep)
{
	int	xinter;
	int	yinter;
	int	up;
	int	right;

	direction_angle(&up, &right, angle);
	data->vhitx = -1;
	yinter = (data->player.y / TILE_SIZE) * TILE_SIZE;
	yinter += TILE_SIZE * right;
	xinter = data->player.x + (yinter - data->player.y) * tan(data->player.angle);
	
	ystep = TILE_SIZE * -2 * !right + TILE_SIZE;
	xstep = TILE_SIZE * tan(data->player.angle);
	if (!up && xstep > 0)
		xstep *= -1;
	if (up && xstep < 0)
		xstep *= -1;
	yinter += -1 * !right;
	// data->vhitx = xinter + xstep * 2;
	// data->vhity = yinter + ystep * 2;
	// return (0);
	while (xinter >= 0 && xinter < HEIGHT && yinter >= 0 && yinter < WIDTH)
	{
		if (data->mp[xinter / TILE_SIZE][yinter / TILE_SIZE] == '1')
		{
			data->vhitx = xinter;
			data->vhity = yinter;
			break ;
		}
		else
		{
			xinter += xstep;
			yinter += ystep;
		}
	}
	return (0);
}

int	cast(t_data *data, float angle)
{
	//horizontal intersection
	h_cast(data, angle, 0, 0);
	v_cast(data, angle, 0, 0);
	return (0);
}



