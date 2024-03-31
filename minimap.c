/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:05:12 by mozennou          #+#    #+#             */
/*   Updated: 2024/03/31 00:47:19 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
				pixel_put(mlx, i + WIDTH / 10, j + HEIGHT / 10, 0X2C7865);
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
		while (j < HEIGHT / 4)
		{
			if (((i - WIDTH / 10) * (i - WIDTH / 10) + (j - HEIGHT / 10) * (j - HEIGHT / 10)) < 8500)
			{
				if (is_wall(data, (data->y + j * 2 - 192) / TILE_SIZE, (data->x + i * 2 - 256) / TILE_SIZE))
					pixel_put(mlx, i, j, 0xFF9800);
				else
					pixel_put(mlx, i, j, 0xD9EDBF);
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
