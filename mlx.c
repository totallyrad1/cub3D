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
	mlx->bf = mlx_get_data_addr(mlx->img, &mlx->pxl_b, &mlx->ln_b, &mlx->endian);
	if (!mlx->bf)
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

int	is_ok(t_data *data, int x, int y)
{
	int a;

	a = data->move_speed / 2;
	if (data->mp[y / TILE_SIZE][x / TILE_SIZE] == '1')
		return (0);
	if (data->mp[(y + a)  / TILE_SIZE][x / TILE_SIZE] == '1'
		|| data->mp[y  / TILE_SIZE][(x + a) / TILE_SIZE] == '1'
		|| data->mp[(y - a)  / TILE_SIZE][x / TILE_SIZE] == '1'
		|| data->mp[y  / TILE_SIZE][(x - a) / TILE_SIZE] == '1')
		return (0);
	return (1);
}

int	keyclick(int ky, void *ptr)
{
	t_strct	*mlx;
	t_data	*dt;
	int		xx;
	int		yy;

	mlx = ptr;
	dt = mlx->data;
	xx = cos(dt->angle) * dt->move_speed;
	yy = sin(dt->angle) * dt->move_speed;
	if (ky == KEY_ESC)
		destroy(mlx);
	else if ((ky == UP_KEY || ky == 126) && is_ok(dt, dt->x + xx, dt->y + yy))
	{
		dt->x += xx;
		dt->y += yy;
	}
	else if ((ky == DOWN_KEY || ky == 125) && is_ok(dt, dt->x - xx, dt->y - yy))
	{
		dt->x -= xx;
		dt->y -= yy;
	}
	else if (ky == LEFT_KEY && is_ok(dt, dt->x + yy, dt->y - xx))
	{
		dt->x += yy;
		dt->y -= xx;
	}
	else if (ky == RIGHT_KEY && is_ok(dt, dt->x - yy, dt->y + xx))
	{
		dt->x -= yy;
		dt->y += xx;
	}
	else if (ky == RRIGHT_KEY)
		dt->angle -= dt->rotation_speed;
	else if (ky == RLEFT_KEY)
		dt->angle += dt->rotation_speed;
	return (0);
}

void	init_events(t_strct *mlx)
{
	mlx_hook(mlx->win, ON_DESTROY, 0, destroy, mlx);
	mlx_hook(mlx->win, ON_KEYDOWN, 0, keyclick, mlx);
}

void	pixel_put(t_strct *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->bf + (y * mlx->ln_b + x * (mlx->pxl_b / 8));
	*(unsigned int *) dst = color;
}