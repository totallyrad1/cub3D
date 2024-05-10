/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:58:42 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/10 14:12:24 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void	draw_map_func(int i, int j, t_strct *mlx, t_data *d)
{
	if (j < HEIGHT / 10 + 10 || j > (HEIGHT / 10) * 9 - 10
		|| i < WIDTH / 10 + 10 || i > (WIDTH / 10) * 9 - 10)
	{
		pixel_put(mlx, i, j, 0x000000);
	}
	else
	{
		if (is_wall(d, (d->y + j * 8 - 960 * 4),
				(d->x + i * 8 - 1024 * 4 - 512 * 2)) == 1)
			pixel_put(mlx, i, j, 0x5F6F52);
		else if (is_wall(d, (d->y + j * 8 - 960 * 4),
				(d->x + i * 8 - 1024 * 4 - 512 * 2)) == 2)
			pixel_put(mlx, i, j, 0x124076);
		else
			pixel_put(mlx, i, j, 0xA9B388);
		if (((i - WIDTH / 2) * (i - WIDTH / 2)
				+ (j - HEIGHT / 2) * (j - HEIGHT / 2)) < 20)
			pixel_put(mlx, i, j, 0XFEFAE0);
	}
}

void	draw_map(t_strct *mlx, t_data *data)
{
	int			i;
	int			j;
	t_4points	p;

	i = WIDTH / 10;
	while (i < (WIDTH / 10) * 9)
	{
		j = HEIGHT / 10;
		while (j < (HEIGHT / 10) * 9)
		{
			draw_map_func(i, j, mlx, data);
			j++;
		}
		i++;
	}
	p = (t_4points){WIDTH / 2, HEIGHT / 2, WIDTH / 2 + cos(data->angle) * 20,
		HEIGHT / 2 + sin(data->angle) * 20};
	direction_line(&p, mlx);
}
