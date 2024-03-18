/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:01:47 by mozennou          #+#    #+#             */
/*   Updated: 2024/03/18 16:00:36 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// render

int main()
{
	t_strct	mlx;
	// t_data data;

	init_graphics(&mlx);
	init_events(&mlx);
	// render(&mlx);
	mlx_loop(mlx.mlx);
}
