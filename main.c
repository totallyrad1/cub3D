/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:01:47 by mozennou          #+#    #+#             */
/*   Updated: 2024/03/18 21:35:14 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// render

int main()
{
	// t_strct	mlx;
	// t_data data;

	if(checkifmapvalid(newmapfn()))
		return (1);
	printf("valid map\n");
// 	init_graphics(&mlx);
// 	init_events(&mlx);
// 	mlx_loop(mlx.mlx);
}
