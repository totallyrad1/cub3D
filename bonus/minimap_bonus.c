/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:05:12 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/10 15:38:26 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void	direction_line(t_4points *p, t_strct *mlx)
{
	int	dx;
	int	dy;
	int	err;
	int	e2;

	dy = abs(p->y2 - p->y1);
	dx = abs(p->x2 - p->x1);
	err = dx - dy;
	while (1)
	{
		pixel_put(mlx, p->x1, p->y1, 0X006400);
		if (p->x1 == p->x2 && p->y1 == p->y2)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			p->x1 += (p->x1 < p->x2) - !(p->x1 < p->x2);
		}
		if (e2 < dx)
		{
			err += dx;
			p->y1 += (p->y1 < p->y2) - !(p->y1 < p->y2);
		}
	}
}

void	player_dot(t_strct *mlx)
{
	int	i;
	int	j;

	i = -5;
	while (i < 5)
	{
		j = -5;
		while (j < 5)
		{
			if ((i * i + j * j) < 20)
				pixel_put(mlx, i + WIDTH / 10, j + HEIGHT / 10, 0XFEFAE0);
			j++;
		}
		i++;
	}
}

void	mini_map_func(int i, int j, t_data *d, t_strct *mlx)
{
	if (((i - WIDTH / 10) * (i - WIDTH / 10)
			+ (j - HEIGHT / 10) * (j - HEIGHT / 10)) < 8500)
	{
		if (is_wall(d, (d->y + j * 16 - 1536),
				(d->x + i * 16 - 2048)) == 1)
			pixel_put(mlx, i, j, 0x5F6F52);
		else if (is_wall(d, (d->y + j * 16 - 1536),
				(d->x + i * 16 - 2048)) == 2)
			pixel_put(mlx, i, j, 0x124076);
		else
			pixel_put(mlx, i, j, 0xA9B388);
	}
	else if (((i - WIDTH / 10) * (i - WIDTH / 10)
			+ (j - HEIGHT / 10) * (j - HEIGHT / 10)) < 10000)
		pixel_put(mlx, i, j, 0);
}

void	mini_map(t_strct *mlx, t_data *data)
{
	int			i;
	int			j;
	t_4points	p;

	i = 0;
	while (i < WIDTH / 5)
	{
		j = 0;
		while (j < HEIGHT / 5 + 5)
		{
			mini_map_func(i, j, data, mlx);
			j++;
		}
		i++;
	}
	player_dot(mlx);
	p = (t_4points){WIDTH / 10, HEIGHT / 10, WIDTH / 10 + cos(data->angle) * 20,
		HEIGHT / 10 + sin(data->angle) * 20};
	direction_line(&p, mlx);
}

void	draw_amo(t_strct *mlx, int amo)
{
	int	i;
	int	m;
	int	j;

	m = (WIDTH - (WIDTH / 10) * 8 - 20) / 8;
	i = (WIDTH / 10) * 8;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT / 15)
		{
			pixel_put(mlx, i, j, 0xFFFFFF);
			if (j > (HEIGHT / 15) - 8 || j < 8
				|| i < ((WIDTH / 10) * 8 + 8) || i > WIDTH - 8)
				pixel_put(mlx, i, j, 0);
			if ((i - (WIDTH / 10) * 8 - 10) < (amo * m)
				&& j < (HEIGHT / 15) - 10
				&& j > 10 && i > ((WIDTH / 10) * 8 + 10) && i < WIDTH - 10
				&& ((i - (WIDTH / 10) * 8 - 10) % m) != 0)
				pixel_put(mlx, i, j, 0x0000FF);
			j++;
		}
		i++;
	}
}
