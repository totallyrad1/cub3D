/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitfn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:32:31 by asnaji            #+#    #+#             */
/*   Updated: 2024/05/09 19:32:33 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void	destroyimages(t_data *data)
{
	if (data->so)
		mlx_destroy_image(data->mlx->mlx, data->so);
	if (data->no)
		mlx_destroy_image(data->mlx->mlx, data->no);
	if (data->ea)
		mlx_destroy_image(data->mlx->mlx, data->ea);
	if (data->we)
		mlx_destroy_image(data->mlx->mlx, data->we);
}

void	destroyanimtext(t_data *data)
{
	if (data->door)
		mlx_destroy_image(data->mlx->mlx, data->door);
	if (data->mlx->anim1)
		mlx_destroy_image(data->mlx->mlx, data->mlx->anim1);
	if (data->mlx->anim2)
		mlx_destroy_image(data->mlx->mlx, data->mlx->anim2);
	if (data->mlx->anim3)
		mlx_destroy_image(data->mlx->mlx, data->mlx->anim3);
	if (data->mlx->anim4)
		mlx_destroy_image(data->mlx->mlx, data->mlx->anim4);
	if (data->mlx->reload1)
		mlx_destroy_image(data->mlx->mlx, data->mlx->reload1);
	if (data->mlx->reload2)
		mlx_destroy_image(data->mlx->mlx, data->mlx->reload2);
	if (data->mlx->reload3)
		mlx_destroy_image(data->mlx->mlx, data->mlx->reload3);
	if (data->mlx->reload4)
		mlx_destroy_image(data->mlx->mlx, data->mlx->reload4);
	if (data->mlx->reload5)
		mlx_destroy_image(data->mlx->mlx, data->mlx->reload5);
}

void	destroymlxptrs(t_data *data)
{
	if (data->mlx->img)
		mlx_destroy_image(data->mlx->mlx, data->mlx->img);
}

void	freemap(t_data *data)
{
	if (data && data->mp)
		free_array(data->mp);
}

void	exit_fn(t_data *data)
{
	destroyanimtext(data);
	destroyimages(data);
	destroymlxptrs(data);
	freemap(data);
	exit(1);
}
