/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils_bonus2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:26:46 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/02 18:26:52 by mozennou         ###   ########.fr       */
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
		return (v);
	}
	data->ver = 0;
	return (h);
}