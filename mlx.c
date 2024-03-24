#include "header.h"

void	init_graphics(t_strct *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		exit(1);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!mlx->win)
		exit(1);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
		exit(1);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while(map[i])
		free(map[i++]);
	free(map);
}

int	destroy(t_strct *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx->mlx);
	free_map(mlx->data->mp);
	exit(0);
	return (0);
}

int	is_ok(t_data *d, int m_x, int m_y)
{
	int	x;
	int	y;

	x = d->player.x + m_x;
	y = d->player.y + m_y;
	if (d->mp[x / d->h][y / d->w] == '1')
		return (0);
	if ((d->mp[(int)(x - d->player.move_speed) / d->h][y / d->w] == '1'  //re
		&& d->mp[x / d->h][(int)(y - d->player.move_speed) / d->w] == '1' ) ||
		(d->mp[(int)(x + d->player.move_speed) / d->h][y / d->w] == '1'
		&& d->mp[x / d->h][(int)(y + d->player.move_speed) / d->w] == '1' ) ||
		(d->mp[(int)(x - d->player.move_speed) / d->h][y / d->w] == '1'
		&& d->mp[x / d->h][(int)(y + d->player.move_speed) / d->w] == '1' ) ||
		(d->mp[(int)(x + d->player.move_speed) / d->h][y / d->w] == '1'
		&& d->mp[x / d->h][(int)(y - d->player.move_speed) / d->w] == '1' ))
		return (0);
	return (1);
}

int	keyclick(int key, void *ptr)
{
	t_strct	*mlx;
	t_data	*data;
	float	xx;
	float	yy;

	mlx = ptr;
	data = mlx->data;
	xx = sin(data->player.angle) * data->player.move_speed;
	yy = cos(data->player.angle) * data->player.move_speed;
	if (key == KEY_ESC)
		destroy(mlx);
	else if (key == UP_KEY && is_ok(data, xx, yy))
	{
		data->player.x += xx;
		data->player.y += yy;
	}
	else if (key == DOWN_KEY && is_ok(data, -xx, -yy))
	{
		data->player.x -= xx;
		data->player.y -= yy;
	}
	else if (key == LEFT_KEY && is_ok(data, -yy, xx))
	{
		data->player.x -= yy;
		data->player.y += xx;
	}
	else if (key == RIGHT_KEY && is_ok(data, yy, -xx))
	{
		data->player.x += yy;
		data->player.y -= xx;
	}
	else if (key == RLEFT_KEY)
		data->player.angle += data->player.rotation_speed;
	else if (key == RRIGHT_KEY)
		data->player.angle -= data->player.rotation_speed;
	render2(data, mlx);
	return (0);
}

void	init_events(t_strct *mlx)
{
	mlx_hook(mlx->win, ON_DESTROY, 0, destroy, mlx);
	mlx_hook(mlx->win, ON_KEYDOWN, 0, keyclick, mlx);
}

void	pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->bf + (y * data->ln_b + x * (data->pxl_b / 8));
	*(unsigned int *) dst = color;
}