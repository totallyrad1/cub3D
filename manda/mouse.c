/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:19:14 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/10 14:28:58 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_events(t_strct *mlx)
{
	mlx_hook(mlx->win, ON_KEYRELEASE, 0, keyrelease, mlx->data);
	mlx_hook(mlx->win, ON_DESTROY, 0, destroy, mlx);
	mlx_hook(mlx->win, ON_KEYDOWN, 0, keyclick, mlx);
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
