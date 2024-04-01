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

int	keyclick(int ky, void *ptr)
{
	t_strct	*mlx;
	t_data	*data;

	mlx = ptr;
	data = mlx->data;
	if (ky == KEY_ESC)
		destroy(mlx);
	else if ((ky == UP_KEY || ky == 126))
		data->walk = 1;
	else if ((ky == DOWN_KEY || ky == 125))
		data->walk = -1;
	else if (ky == LEFT_KEY)
		data->left_right = 1;
	else if (ky == RIGHT_KEY)
		data->left_right = -1;
	else if (ky == RRIGHT_KEY)
		data->turn = -1;
	else if (ky == RLEFT_KEY)
		data->turn = 1;
	else if (ky == 15 && !gun_sound("./sounds/reload.wav"))
		data->amo = 0;
	else if (ky == 12)
	{
		if (!data->hide)
		{
			mlx_mouse_show();
			data->hide = 1;
		}
		else
		{
			mlx_mouse_hide();
			mlx_mouse_move(data->mlx->win, (data->angle /((M_PI / 180) / 1.8)) + WIDTH / 2, HEIGHT / 2);
			data->hide = 0;
		}
	}
	return (0);
}

int	keyrelease(int ky, void *ptr)
{
	t_data *data;

	data = ptr;
	if (ky == UP_KEY || ky == 126 || ky == DOWN_KEY || ky == 125)
		data->walk = 0;
	else if (ky == LEFT_KEY || ky == RIGHT_KEY)
		data->left_right = 0;
	else if (ky == RRIGHT_KEY || ky == RLEFT_KEY)
		data->turn = 0;
	return (0);
}



int	mousemove(int x, int y, void *ptr)
{
	t_data *data = ptr;
	static int	res;
	
	if (!data->hide)
	{
		if (x < 0 || x > WIDTH)
		{
			data->old_angle = data->angle;
			mlx_mouse_move(data->mlx->win, WIDTH / 2, HEIGHT / 2);
		}
		else
		{
			res = WIDTH / 2 - x;
			data->angle = -res * ((M_PI / 180) / 1.8);
		}
	}
	return (0);
}

int	mouseclick(int ky, int x, int y, void *ptr)
{
	t_data	*data = ptr;

	if (ky == 1)
	{
		if (data->amo == 8)
			gun_sound("./sounds/test.wav");
		else if (!gun_sound("./sounds/gun_shot.wav"))
		{
			data->test = -0.8;
			data->amo++;
		}
	}
	else if (ky == 2)
		data->scope = !data->scope;
	return (0);
}

int	mouseup(int ky, int x, int y, void *ptr)
{
	t_data	*data = ptr;

	if (ky == 1)
		data->test = 0;
}

void	init_events(t_strct *mlx)
{
	mlx_hook(mlx->win, ON_KEYRELEASE, 0, keyrelease, mlx->data);
	mlx_hook(mlx->win, ON_DESTROY, 0, destroy, mlx);
	mlx_hook(mlx->win, ON_KEYDOWN, 0, keyclick, mlx);
	mlx_hook(mlx->win, ON_MOUSEDOWN, 0, mouseclick, mlx->data);
	mlx_hook(mlx->win, ON_MOUSEUP, 0, mouseup, mlx->data);
	mlx_hook(mlx->win, ON_MOUSEMOVE, 0, mousemove, mlx->data);
}

void	pixel_put(t_strct *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->bf + (y * mlx->ln_b + x * (mlx->pxl_b / 8));
	*(unsigned int *) dst = color;
}