/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:01:47 by mozennou          #+#    #+#             */
/*   Updated: 2024/03/18 17:54:04 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


#include <string.h>

// void	color_it(int m, int n, t_img *img, int wlen, int hlen)
// {
// 	for(int i = 0; i < wlen; i++)
// 	{
// 		for (int j = 0; j < hlen; j++)
// 		{
// 			pixel_put(img, m * wlen + i, n *hlen + j, 0x0000FF);
// 		}
// 	}
// }

void	render(char map[10][10], t_strct	*mlx)
{
	t_img	img;

	img.bf = mlx_get_data_addr(mlx->img, &img.pxl_b, &img.ln_b, &img.endian);
	int	wlen = WIDTH / 10, hlen = HEIGHT / 10;
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (map[i / wlen][j / hlen])
				pixel_put(&img, i, j, 0x0000FF);
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int main()
{
	t_strct	mlx;

	init_graphics(&mlx);
	init_events(&mlx);
	char map[10][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 0, 0, 0, 0, 0, 1, 1, 1}, {1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},{1, 1, 1, 1, 1, 1, 1, 1, 1, 1} ,{1, 1, 1, 1, 1, 1, 1, 1, 1, 1} ,{1, 1, 1, 1, 1, 1, 1, 1, 1, 1} ,{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	// char **test = (char **)map;
	render(map, &mlx);
	mlx_loop(mlx.mlx);
}
