/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:47:17 by mozennou          #+#    #+#             */
/*   Updated: 2024/04/01 22:31:20 by asnaji           ###   ########.fr       */
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
	data->hide = 1;
	data->scope = 0;
	data->test = 0;
	data->f_color = -1;
	data->c_color = -1;
	data->amo = 0;
	data->lc_tillstartofmap = 0;
}

void	init_data2(t_data *data)
{
	data->x = data->x * TILE_SIZE + TILE_SIZE / 2;
	data->y = data->y * TILE_SIZE + TILE_SIZE / 2;
	data->move_speed = 3;
	data->rotation_speed = 2 * (M_PI / 180);
}

t_ray	*ray_generator(t_data *data)
{
	t_ray	*rays = malloc(sizeof(t_ray) * WIDTH);
	double angle = data->angle - (FOV / 2);
	float res = FOV / WIDTH;
	for (int i = 0; i < WIDTH; i++)
	{
		angle = normalize(angle);
		rays[i].angle = angle;
		rays[i].dis = cast(data, angle) * cos(angle - data->angle);
		rays[i].hitx = data->hhitx;
		rays[i].hity = data->hhity;
		rays[i].ver = data->ver;
		rays[i].wallprjct = (TILE_SIZE / rays[i].dis) * DISPROJ;
		angle += res;
	}
	return (rays);
}

int	is_ok(t_data *data, int x, int y)
{
	int a;

	a = data->move_speed;
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

	xx = cos(data->angle) * (data->move_speed - data->scope * data->move_speed / 2);
	yy = sin(data->angle) * (data->move_speed - data->scope * data->move_speed / 2);
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
	data->angle += data->turn * data->rotation_speed * data->hide;
	if (data->turn && !data->hide)
		mlx_mouse_move(data->mlx->win, (int)((data->angle /((M_PI / 180) / 1.8)) + WIDTH / 2) % WIDTH, HEIGHT / 2);
}

void	floor_ceiling(t_strct *mlx, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			if (j > HEIGHT / 2 - data->test * 100)
				pixel_put(mlx, i, j, data->f_color);
			else	
				pixel_put(mlx, i, j, data->c_color);
			j++;
		}
		i++;
	}
}

// void	walls(t_ray *rays, t_strct *mlx)
// {
// 	t_data	*d;
// 	int	i;
// 	int	j;

// 	d = mlx->data;
// 	i = 0;
// 	while (i < WIDTH)
// 	{
// 		j = 0;
// 		while (j < HEIGHT)
// 		{
// 			if (j > (HEIGHT / 2 - d->test * 100 - rays[i].wallprjct / 2) && j < (HEIGHT / 2 - d->test * 100+ rays[i].wallprjct / 2))
// 			{
				
// 				pixel_put(mlx, i, j, 0xFFFFFF);
// 			}	
// 			if (((i - WIDTH / 2) * (i - WIDTH / 2) + (j - HEIGHT / 2) * (j - HEIGHT / 2)) < 10)
// 				pixel_put(mlx, i, j, 0x000000);
// 			j++;
// 		}
// 		i++;
// 	}
// }

unsigned int getpixelcolor(char *tex, int b, int texOffset)
{
	unsigned int color;
	unsigned char red = tex[texOffset];
	unsigned char green = tex[texOffset + 1];
	unsigned char blue = tex[texOffset + 2];
	unsigned char alpha = tex[texOffset + 3];
	
	color = 0;
	color |= red;
	color |= green << 8;
	color |= blue << 16;
	color |= alpha << 24;
	return (color);
}

void	walls(t_ray *rays, t_strct *mlx)
{
	t_data	*d;
	int	i;
	int	j;
	unsigned int color;

	int b;
	int l;
	int x;
	char *tex = mlx_get_data_addr(mlx->data->so, &b, &l, &x);

	d = mlx->data;
	i = 0;
	while (i < WIDTH)
	{
		float distanceProjPlane = (WIDTH / 2) / tan(rays[i].angle / 2);
        float projectedWallHeight = (TILE_SIZE / rays[i].dis) * DISPROJ;
		
		int wallStripHeight = (int)projectedWallHeight;
		
		int wallTopPixel = (HEIGHT / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

		int wallBottomPixel = (HEIGHT / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > HEIGHT ? HEIGHT : wallBottomPixel;

		int textureOffsetX;
        if (rays[i].ver)
            textureOffsetX = (int)rays[i].hity % TILE_SIZE;
        else
            textureOffsetX = (int)rays[i].hitx % TILE_SIZE;
		j = 0;
		while (j < HEIGHT)
		{
			if (j > (HEIGHT / 2 - d->test * 100 - rays[i].wallprjct / 2) && j < (HEIGHT / 2 - d->test * 100+ rays[i].wallprjct / 2))
			{
				int distanceFromTop = j + (wallStripHeight / 2) - (HEIGHT / 2);
				int textureOffsetY = distanceFromTop * ((float)64 / wallStripHeight);
				
				color = getpixelcolor(tex, b, (TILE_SIZE * textureOffsetY + textureOffsetX) * (b / 8));
				pixel_put(mlx, i, j, color);
			}	
			if (((i - WIDTH / 2) * (i - WIDTH / 2) + (j - HEIGHT / 2) * (j - HEIGHT / 2)) < 10)
				pixel_put(mlx, i, j, 0x000000);
			j++;
		}
		i++;
	}
}

// void textrues(t_ray *rays, t_strct *mlx)
// {
// 	int b;
// 	int l;
// 	int x;
// 	char *tex = mlx_get_data_addr(mlx->data->so, &b, &l, &x);

// 	for (int i = 0; i < WIDTH; i++) {
//         float perpDistance = rays[i].dis;
//         float distanceProjPlane = (WIDTH / 2) / tan(rays[i].angle / 2);
//         float projectedWallHeight = (TILE_SIZE / rays[i].dis) * DISPROJ;

//         int wallStripHeight = (int)projectedWallHeight;

//         int wallTopPixel = (HEIGHT / 2) - (wallStripHeight / 2);
//         wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

//         int wallBottomPixel = (HEIGHT / 2) + (wallStripHeight / 2);
//         wallBottomPixel = wallBottomPixel > HEIGHT ? HEIGHT : wallBottomPixel;

//         // calculate texture offset X
//         int textureOffsetX;
//         if (rays[i].ver)
//             textureOffsetX = (int)rays[i].hity % TILE_SIZE;
//         else
//             textureOffsetX = (int)rays[i].hitx % TILE_SIZE;

//         for (int y = wallTopPixel; y <= wallBottomPixel; y++) {
//             int distanceFromTop = y + (wallStripHeight / 2) - (HEIGHT / 2);
//             int textureOffsetY = distanceFromTop * ((float)TILE_SIZE / wallStripHeight);

// 			int texOffset = (TILE_SIZE * textureOffsetY + textureOffsetX) * (b / 8);
// 			unsigned char red = tex[texOffset];
// 			unsigned char green = tex[texOffset + 1];
// 			unsigned char blue = tex[texOffset + 2];
// 			unsigned char alpha = tex[texOffset + 3];
            
// 			unsigned int color = 0;
// 			color |= tex[texOffset];
// 			color |= tex[texOffset + 1] << 8;
// 			color |= tex[texOffset + 2] << 16;
// 			color |= alpha << 24;
//             pixel_put(mlx, i, y, color);
//         }
//     }
// }

int	render3d(void *ptr)
{
	t_data *data;
	t_strct	*mlx;
	t_ray	*rays;

	data = ptr;
	mlx = data->mlx;
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
	floor_ceiling(mlx, data);
	walls(rays, mlx);
	// textrues(rays, mlx);
	if (data->scope)
		draw_scope(mlx);
	if (data->map)
		draw_map(mlx, data);
	else
	{
		mini_map(mlx, data);
		draw_amo(mlx, 8 - data->amo);
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
	init_data1(&mlx, &data);
	init_graphics(&mlx);
	if(parsing(&data, &mlx, av[1]) == -1)
		return (1);
	if(checkifmapvalid(&data))
		return (1);
	init_data2(&data);
	init_events(&mlx);
	mlx_loop_hook(mlx.mlx, render3d, &data);
	mlx_loop(mlx.mlx);
}
