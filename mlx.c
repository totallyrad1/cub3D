/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:18:54 by asnaji            #+#    #+#             */
/*   Updated: 2024/03/18 16:26:21 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_graphics(t_strct *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		exit(1);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!mlx->win)
		exit(1);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
		exit(1);
}

int	destroy(t_strct *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
}

int	keyclick(int key, void *ptr)
{
	t_strct	*mlx;

	mlx = ptr;
	if (key == KEY_ESC)
		destroy(mlx);
	return (0);
}

void	init_events(t_strct *mlx)
{
	mlx_hook(mlx->win, ON_DESTROY, 0, destroy, mlx);
	mlx_hook(mlx->win, ON_KEYDOWN, 0, keyclick, mlx);
}

void	pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->bf + (y * data->ln_b + x * (data->pxl_b / 8));
	*(unsigned int *) dst = color;
}