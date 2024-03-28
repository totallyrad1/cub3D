#include "header.h"

void	init_data1(t_strct *mlx, t_data *data)
{
	data->NO = NULL;
	data->SO = NULL;
	data->EA = NULL;
	data->WE = NULL;
	data->walk = 0;
	data->turn = 0;
	data->left_right = 0;
	mlx->data = data;
	data->mlx = mlx;
}

void	init_data2(t_strct *mlx, t_data *data)
{
	data->x = data->x * TILE_SIZE + TILE_SIZE / 2;
	data->y = data->y * TILE_SIZE + TILE_SIZE / 2;
	data->move_speed = 3;
	data->rotation_speed = 2 * (M_PI / 180);
}

int in_line(int x1, int y1, int x2, int y2, int j, int i)
{
    int cross = (x2 - x1) * (j - y1) - (y2 - y1) * (i - x1);
    int distance = abs(cross) / sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    
    if (distance <= 0) {
        int minX = x1 < x2 ? x1 : x2;
        int maxX = x1 > x2 ? x1 : x2;
        int minY = y1 < y2 ? y1 : y2;
        int maxY = y1 > y2 ? y1 : y2;

        if (i >= minX && i <= maxX && j >= minY && j <= maxY) {
            return 1; 
        }
    }
    return 0; 
}

int	circle(int i, int j, t_data *data)
{
	i = data->x - i;
	j = data->y - j;
	if ((i * i + j * j) < 20)
		return (1);
	return (0);
}

t_ray *test(t_data *data)
{
	int	m = WIDTH;
	t_ray	*rays = malloc(sizeof(t_ray) * m);
	double angle = data->angle - (FOV / 2);
	float res = FOV / m;
	for (int i = 0; i < m; i++)
	{
		angle = normalize(angle);
		rays[i].dis = cast(data, angle);
		rays[i].hitx = data->hhitx;
		rays[i].hity = data->hhity;
		rays[i].ver = data->ver;
		angle += res;
	}
	return (rays);
}

int func(t_data *data, t_ray *rays, int i, int j)
{
	for (int k = 0; k < 200; k++)
	{
		if (in_line(data->x, data->y, rays[k].hitx, rays[k].hity, j, i) && rays[k].hitx != -1 && rays[k].hity != -1)
		{
			if (rays[k].ver)
				return (1);
			else
				return (2);
		}
	}
	return (0);
}
void wa333(int x1, int y1, int x2, int y2, t_strct *mlx, int l)
{
	int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
		if (l)
			pixel_put(mlx, x1, y1, 0XFF0000);
		else
			pixel_put(mlx, x1, y1, 0X00FF00);
        if (x1 == x2 && y1 == y2) {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
	}
}
void func1(t_data *data, t_ray *rays,t_strct *mlx)
{
	int x1, y1, x2, y2;
	for (int i = 0; i < WIDTH; i++)
	{
		x1 = data->x;
		y1 = data->y;
		x2 = rays[i].hitx;
		y2 = rays[i].hity;
		wa333(x1, y1, x2, y2, mlx, rays[i].ver);
	}
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

void	update(t_data *data)
{
	int	xx;
	int	yy;

	xx = cos(data->angle) * data->move_speed;
	yy = sin(data->angle) * data->move_speed;
	if (data->walk && is_ok(data, data->x + data->walk * xx, data->y + data->walk * yy))
	{
		data->x += data->walk * xx;
		data->y += data->walk * yy;
	}
	if (data->left_right && is_ok(data, data->x + data->left_right * yy, data->y - data->left_right * xx))
	{
		data->x += data->left_right * yy;
		data->y -= data->left_right * xx;
	}
	data->angle += data->turn * data->rotation_speed;
}

int	render(void *ptr)
{
	int	i;
	int	j;
	t_data *data = ptr;
	t_strct	*mlx = data->mlx;
	t_ray	*rays;

	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
		exit(1);
	mlx->bf = mlx_get_data_addr(mlx->img, &mlx->pxl_b, &mlx->ln_b, &mlx->endian);
	if (!mlx->bf)
		exit(1);
	i = 0;
	j = 0;
	int f = 0;
	update(data);
	rays = test(data);
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			// f = func(data, rays, i, j);
			if (circle(i, j, data))
				pixel_put(mlx, i, j, 0xFF0000);
			// else if (in_line(data->x, data->y, data->x + cos(data->angle) * 20, data->y + sin(data->angle) * 20, j, i))
			// 	pixel_put(mlx, i, j, 0xFFFFFF);
			// else if (f == 1)
			// 		pixel_put(mlx, i, j, 0x00FF00); //green vertiacal
			// else if (f == 2)
			// 		pixel_put(mlx, i, j, 0xFF0000); //red horizontal
			else if (data->mp[j / TILE_SIZE][i / TILE_SIZE] == '1' || !(i % TILE_SIZE) || !(j % TILE_SIZE))
				pixel_put(mlx, i, j, 0x00AAAA);
			j++;
		}
		i++;
	}
	func1(data, rays, mlx);
	free(rays);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	// free(mlx->)
	return (0);
}

int main(int ac, char **av)
{
	t_strct	mlx;
	t_data data;

	if (ac != 2)
		return(wrerror("invalid arguments"), 1);
	if (checkfilename(av[1]) == -1)
		return (1);
	if (checkvalidchars(av[1]) == -1)
		return (1);
	init_data1(&mlx, &data);
	init_graphics(&mlx);
	if(parse_everything(&data, &mlx, av[1]) == -1)
		return (1);
	if(checkifmapvalid(&data))
		return (1);
	init_data2(&mlx, &data);
	init_events(&mlx);
	mlx_loop_hook(mlx.mlx, render, &data);
	mlx_loop(mlx.mlx);
}
