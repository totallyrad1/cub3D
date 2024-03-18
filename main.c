/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:01:47 by mozennou          #+#    #+#             */
/*   Updated: 2024/03/18 16:28:37 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


#include <string.h>

void	color_it(int m, int n, t_img *img, int wlen, int hlen)
{
	for(int i = 0; i < wlen; i++)
	{
		for (int j = 0; j < hlen; j++)
		{
			pixel_put(img, m + i, n + j, 0x0000FF);
		}
	}
}

void	render(char **map, t_strct	*mlx)
{
	t_img	img;

	img.bf = mlx_get_data_addr(mlx->img, &img.pxl_b, &img.ln_b, &img.endian);
	int	wlen = WIDTH / strlen(map[0]), hlen = HEIGHT / len(map);
	for (int i = 0; map[i]; i++)
	{
		for (int j = 0; map[i][j]; j++)
		{
			if (map[i][j])
				color_it(i, j, &img, wlen, hlen);
		}
	}
}

int main()
{
	t_strct	mlx;

	init_graphics(&mlx);
	init_events(&mlx);
	mlx_loop(mlx.mlx);
}
