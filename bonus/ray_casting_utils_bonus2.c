/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils_bonus2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:26:46 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/10 14:26:01 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

double	cast(t_data *data, double angle)
{
	double	h;
	double	v;

	h = hcast(data, angle, 0, 0);
	v = vcast(data, angle, 0, 0);
	if (h > v)
	{
		data->ver = 1;
		data->hhitx = data->vhitx;
		data->hhity = data->vhity;
		data->hdoor = data->vdoor;
		return (v);
	}
	data->ver = 0;
	return (h);
}

void	draw_shoot(t_data *data, t_strct *mlx)
{
	if (data->texid < 3)
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			mlx->anim1, WIDTH / 2 - 150, HEIGHT / 2);
	else if (data->texid < 5)
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			mlx->anim2, WIDTH / 2 - 150, HEIGHT / 2);
	else if (data->texid < 8)
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			mlx->anim3, WIDTH / 2 - 150, HEIGHT / 2);
	else if (data->texid < 13)
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			mlx->anim4, WIDTH / 2 - 150, HEIGHT / 2);
}

void	draw_reload(t_data *data, t_strct *mlx)
{
	if (data->texid > -5)
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			mlx->reload1, WIDTH / 2 - 150, HEIGHT / 2);
	else if (data->texid > -10)
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			mlx->reload2, WIDTH / 2 - 150, HEIGHT / 2);
	else if (data->texid > -15)
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			mlx->reload3, WIDTH / 2 - 150, HEIGHT / 2);
	else if (data->texid > -20)
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			mlx->reload4, WIDTH / 2 - 150, HEIGHT / 2);
	else if (data->texid > -25)
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			mlx->reload5, WIDTH / 2 - 150, HEIGHT / 2);
}
