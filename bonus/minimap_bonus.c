/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:05:12 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/02 14:18:23 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void direction_line(int x1, int y1, int x2, int y2, t_strct *mlx)
{
	int	dx;
	int	dy;
	int	err;

	dy = abs(y2 - y1);
	dx = abs(x2 - x1);
	err = dx - dy;
	while (1) {
		pixel_put(mlx, x1, y1, 0X006400);
		if (x1 == x2 && y1 == y2) {
			break;
		}
		int e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x1 += (x1 < x2) - !(x1 < x2);
		}
		if (e2 < dx) {
			err += dx;
			y1 += (y1 < y2) - !(y1 < y2);
		}
	}
}

void	player_dot(t_strct *mlx)
{
	int i, j;
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

void	mini_map(t_strct *mlx, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH / 5)
	{
		j = 0;
		while (j < HEIGHT / 5 + 5)
		{
			if (((i - WIDTH / 10) * (i - WIDTH / 10) + (j - HEIGHT / 10) * (j - HEIGHT / 10)) < 8500)
			{
				if (is_wall(data, (data->y + j * 16 - 192 * 8), (data->x + i * 16 - 256 * 8)) == 1)
					pixel_put(mlx, i, j, 0x5F6F52);
				else if (is_wall(data, (data->y + j * 16 - 192 * 8), (data->x + i * 16 - 256 * 8)) == 2)
					pixel_put(mlx, i, j, 0x124076);
				else
					pixel_put(mlx, i, j, 0xA9B388);
			}
			else if (((i - WIDTH / 10) * (i - WIDTH / 10) + (j - HEIGHT / 10) * (j - HEIGHT / 10)) < 10000)
					pixel_put(mlx, i, j, 0);
			j++;
		}
		i++;
	}
	player_dot(mlx);
	direction_line(WIDTH / 10, HEIGHT / 10, WIDTH / 10 + cos(data->angle) * 20,
		HEIGHT / 10 + sin(data->angle) * 20, mlx);
}

void draw_amo(t_strct *mlx, int amo)
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
			if (j > (HEIGHT / 15) - 8 || j < 8 || i < ((WIDTH / 10) * 8 + 8) || i > WIDTH - 8)
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

void	draw_map(t_strct *mlx, t_data *data)
{
	int	i;
	int	j;

	i = WIDTH / 10;
	while (i < (WIDTH / 10) * 9)
	{
		j = HEIGHT / 10;
		while (j < (HEIGHT / 10) * 9)
		{
			if (j < HEIGHT / 10 + 10 || j > (HEIGHT / 10) * 9 - 10 || i < WIDTH / 10 + 10 || i > (WIDTH / 10) * 9 - 10)
			{
				pixel_put(mlx, i, j, 0x000000);
			}
			else
			{
				if (is_wall(data, (data->y + j * 8 - 960 * 4), (data->x + i * 8 - 1024 * 4  - 512 * 2)) == 1)
					pixel_put(mlx, i, j, 0x5F6F52);
				else if (is_wall(data, (data->y + j * 8 - 960 * 4), (data->x + i * 8 - 1024 * 4  - 512 * 2)) == 2)
					pixel_put(mlx, i, j, 0x124076);
				else
					pixel_put(mlx, i, j, 0xA9B388);
				if (((i - WIDTH / 2) * (i - WIDTH / 2) + (j - HEIGHT / 2) * (j - HEIGHT / 2)) < 10)
					pixel_put(mlx, i, j, 0XFEFAE0);
			}
			j++;
		}
		i++;
	}
	direction_line(WIDTH / 2, HEIGHT / 2, WIDTH / 2 + cos(data->angle) * 20,
		HEIGHT / 2 + sin(data->angle) * 20, mlx);
}
