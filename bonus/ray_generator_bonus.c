/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_generator_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:09:10 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/10 14:13:19 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void	init_data1(t_strct *mlx, t_data *data)
{
	data->no = NULL;
	data->so = NULL;
	data->ea = NULL;
	data->we = NULL;
	data->door = NULL;
	data->walk = 0;
	data->turn = 0;
	data->left_right = 0;
	mlx->data = data;
	data->mlx = mlx;
	data->hide = 1;
	data->f_color = -1;
	data->c_color = -1;
	data->amo = 0;
	data->lc_tillstartofmap = 0;
	data->texid = 0;
	mlx->texid1 = 0;
	data->map = 0;
	data->mp = NULL;
}

void	init_data2(t_data *data)
{
	data->x = data->x * TILE_SIZE + TILE_SIZE / 2;
	data->y = data->y * TILE_SIZE + TILE_SIZE / 2;
	data->rotation_speed = 2 * (M_PI / 180);
}

t_ray	*ray_generator(t_data *data)
{
	t_ray	*rays;
	double	angle;
	int		i;

	angle = data->angle - (FOV / 2);
	rays = malloc(sizeof(t_ray) * WIDTH);
	if (!rays)
		exit(1);
	update(data);
	i = 0;
	while (i < WIDTH)
	{
		angle = normalize(angle);
		rays[i].angle = angle;
		rays[i].dis = cast(data, angle) * cos(angle - data->angle);
		rays[i].hitx = data->hhitx;
		rays[i].hity = data->hhity;
		rays[i].door = data->hdoor;
		rays[i].ver = data->ver;
		rays[i].wallprjct = (TILE_SIZE / rays[i].dis) * DISPROJ;
		angle += FOV / WIDTH;
		i++;
	}
	return (rays);
}

int	is_ok(t_data *data, int x, int y)
{
	int	a;

	a = MOVE_SPEED;
	if (data->mp[y / TILE_SIZE][x / TILE_SIZE] == '1')
		return (0);
	if (data->mp[(y + a) / TILE_SIZE][x / TILE_SIZE] == '1'
		|| data->mp[y / TILE_SIZE][(x + a) / TILE_SIZE] == '1'
		|| data->mp[(y - a) / TILE_SIZE][x / TILE_SIZE] == '1'
		|| data->mp[y / TILE_SIZE][(x - a) / TILE_SIZE] == '1')
		return (0);
	return (1);
}

void	is_door(t_data *data, int m, int l)
{
	if (!l)
	{
		if (m == 2)
			data->hdoor = 1;
	}
	else
	{
		if (m == 2)
			data->vdoor = 1;
	}
}
