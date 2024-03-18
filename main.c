/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:01:47 by mozennou          #+#    #+#             */
/*   Updated: 2024/03/18 14:45:25 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
