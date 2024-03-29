/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:47:17 by mozennou          #+#    #+#             */
/*   Updated: 2024/03/29 22:14:11 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_data1(t_strct *mlx, t_data *data)
{
	data->no = NULL;
	data->so = NULL;
	data->ea = NULL;
	data->we = NULL;
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

t_ray *ray_generator(t_data *data)
{
	t_ray	*rays = malloc(sizeof(t_ray) * WIDTH);
	double angle = data->angle - (FOV / 2);
	float res = FOV / WIDTH;
	for (int i = 0; i < WIDTH; i++)
	{
		angle = normalize(angle);
		rays[i].dis = cast(data, angle) * cos(angle - data->angle);
		rays[i].hitx = data->hhitx;
		rays[i].hity = data->hhity;
		rays[i].wallprjct = (TILE_SIZE / rays[i].dis) * DISPROJ;
		angle += res;
	}
	return (rays);
}

void wa333(int x1, int y1, int x2, int y2, t_strct *mlx)
{
	int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
		pixel_put(mlx, x1, y1, 0XFFFFFF);
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
		wa333(x1, y1, x2, y2, mlx);
	}
}

void	func2(t_data *data, t_strct *mlx)
{
	int x = data->x, y = data->y;
	for (int i = -5; i < 5; i++)
	{
		for (int j = -5; j < 5; j++)
		{
			if ((i * i + j * j) < 20)
				pixel_put(mlx, i + data->x, j + data->y, 0XFF0000);
		}
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

int	render2d(void *ptr)
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
	rays = ray_generator(data);
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			if (data->mp[j / TILE_SIZE][i / TILE_SIZE] == '1' || !(i % TILE_SIZE) || !(j % TILE_SIZE))
				pixel_put(mlx, i, j, 0x00AAAA);
			j++;
		}
		i++;
	}
	func1(data, rays, mlx);
	func2(data, mlx);
	free(rays);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}

int	render3d(void *ptr)
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
		exit(1);								//free the map
	mlx->bf = mlx_get_data_addr(mlx->img, &mlx->pxl_b, &mlx->ln_b, &mlx->endian);
	if (!mlx->bf)
		exit(1);
	update(data);
	rays = ray_generator(data);
	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			if (j < HEIGHT / 2)
				pixel_put(mlx, i, j, data->f_color);
			else	
				pixel_put(mlx, i, j, data->c_color);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			if (j > (HEIGHT / 2 - rays[i].wallprjct / 2) && j < (HEIGHT / 2 + rays[i].wallprjct / 2))
				pixel_put(mlx, i, j, 0xFFFFFF);
			j++;
		}
		i++;
	}
	free(rays);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
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
	mlx_loop_hook(mlx.mlx, render3d, &data);
	mlx_loop(mlx.mlx);
}
