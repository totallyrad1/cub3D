/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:19:14 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/10 14:30:31 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

int	mousemove(int x, int y, void *ptr)
{
	t_data		*data;
	static int	res;

	data = ptr;
	(void)y;
	if (!data->hide)
	{
		if (x < 0 || x > WIDTH)
		{
			mlx_mouse_move(data->mlx->win, WIDTH / 2, HEIGHT / 2);
		}
		else
		{
			res = WIDTH / 2 - x;
			data->angle = -res * 0.009696273622;
		}
	}
	return (0);
}

int	mouseclick(int ky, int x, int y, void *ptr)
{
	t_data	*data;

	data = ptr;
	(void)y;
	(void)x;
	if (ky == 1)
	{
		if (data->amo != 8)
		{
			data->texid = 10;
			data->amo++;
		}
	}
	return (0);
}

void	init_events(t_strct *mlx)
{
	mlx_hook(mlx->win, ON_KEYRELEASE, 0, keyrelease, mlx->data);
	mlx_hook(mlx->win, ON_DESTROY, 0, destroy, mlx);
	mlx_hook(mlx->win, ON_KEYDOWN, 0, keyclick, mlx);
	mlx_hook(mlx->win, ON_MOUSEDOWN, 0, mouseclick, mlx->data);
	mlx_hook(mlx->win, ON_MOUSEMOVE, 0, mousemove, mlx->data);
}

void	pixel_put(t_strct *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->bf + (y * mlx->ln_b + x * (mlx->pxl_b / 8));
	*(unsigned int *) dst = color;
}

int	destroy(t_strct *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx->mlx);
	free_map(mlx->data->mp);
	exit(0);
	return (0);
}
