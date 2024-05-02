/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:21:10 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/02 16:28:56 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void	update(t_data *data)
{
	double	xx;
	double	yy;

	data->angle = normalize(data->angle);
	xx = (cos(data->angle) * (MOVE_SPEED));
	yy = (sin(data->angle) * (MOVE_SPEED));
	if (data->walk && is_ok(data, data->x + data->walk * xx,
			data->y + data->walk * yy))
	{
		data->x += data->walk * xx;
		data->y += data->walk * yy;
	}
	if (data->left_right && is_ok(data, data->x + data->left_right * yy,
			data->y - data->left_right * xx))
	{
		data->x += data->left_right * yy;
		data->y -= data->left_right * xx;
	}
	data->angle += data->turn * data->rotation_speed * data->hide;
	if (data->turn && !data->hide)
		mlx_mouse_move(data->mlx->win,
			(int)((data->angle / ((M_PI / 180) / 1.8))
				+ WIDTH / 2) % WIDTH, HEIGHT / 2);
}

void	floor_ceiling(t_strct *mlx, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			if (j < HEIGHT / 2)
				pixel_put(mlx, i, j, data->f_color);
			else
				pixel_put(mlx, i, j, data->c_color);
			j++;
		}
		i++;
	}
}

unsigned int	getpixelcolor(char *tex, int b, int texOffset)
{
	unsigned int	color;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	unsigned char	alpha;

	red = tex[texOffset];
	green = tex[texOffset + 1];
	blue = tex[texOffset + 2];
	alpha = tex[texOffset + 3];
	color = 0;
	color |= red;
	color |= green << 8;
	color |= blue << 16;
	color |= alpha << 24;
	return (color);
}

void	*getwalltexture(t_ray *rays, t_strct *mlx, int i)
{
	if (rays[i].angle >= E && rays[i].angle <= S)
	{
		if (rays[i].ver)
			return (mlx->data->ea);
		return (mlx->data->so);
	}
	else if (rays[i].angle >= S && rays[i].angle <= W)
	{
		if (rays[i].ver)
			return (mlx->data->we);
		return (mlx->data->so);
	}
	else if (rays[i].angle >= W && rays[i].angle <= N)
	{
		if (rays[i].ver)
			return (mlx->data->we);
		return (mlx->data->no);
	}
	else
	{
		if (rays[i].ver)
			return (mlx->data->ea);
		return (mlx->data->no);
	}
}

void	*getanimetex(t_strct *mlx)
{
	if (mlx->texid1 < 10)
		return (mlx->kirby1);
	else if (mlx->texid1 < 20)
		return (mlx->kirby2);
	else if (mlx->texid1 < 30)
		return (mlx->kirby3);
	else if (mlx->texid1 < 40)
		return (mlx->kirby4);
	else if (mlx->texid1 < 50)
		return (mlx->kirby5);
	else if (mlx->texid1 < 60)
		return (mlx->kirby6);
	return (mlx->kirby7);
}