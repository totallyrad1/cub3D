/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:47:17 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/09 16:16:49 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

int	initanimtex(t_strct *mlx)
{
	int	w;
	int	h;

	mlx->data->door = mlx_xpm_file_to_image(mlx->mlx, "./tex/512_door.xpm", &w, &h);
	if (checkandreturn(w, h, mlx->data->door) == -1)
		return (-1);
	mlx->anim1 = mlx_xpm_file_to_image(mlx->mlx, "./tet/shoot1.xpm", &w, &h);
	if (checkandreturn(512, 512, mlx->anim1) == -1)
		return (-1);
	mlx->anim2 = mlx_xpm_file_to_image(mlx->mlx, "./tet/shoot3.xpm", &w, &h);
	if (checkandreturn(512, 512, mlx->anim2) == -1)
		return (-1);
	mlx->anim3 = mlx_xpm_file_to_image(mlx->mlx, "./tet/shoot4.xpm", &w, &h);
	if (checkandreturn(512, 512, mlx->anim3) == -1)
		return (-1);
	mlx->anim4 = mlx_xpm_file_to_image(mlx->mlx, "./tet/shoot5.xpm", &w, &h);
	if (checkandreturn(512, 512, mlx->anim4) == -1)
		return (-1);
	mlx->reload1 = mlx_xpm_file_to_image(mlx->mlx, "./tet/reload0.xpm", &w, &h);
	if (checkandreturn(512, 512, mlx->reload1) == -1)
		return (-1);
	mlx->reload2 = mlx_xpm_file_to_image(mlx->mlx, "./tet/reload1.xpm", &w, &h);
	if (checkandreturn(512, 512, mlx->reload2) == -1)
		return (-1);
	mlx->reload3 = mlx_xpm_file_to_image(mlx->mlx, "./tet/reload2.xpm", &w, &h);
	if (checkandreturn(512, 512, mlx->reload3) == -1)
		return (-1);
	mlx->reload4 = mlx_xpm_file_to_image(mlx->mlx, "./tet/reload3.xpm", &w, &h);
	if (checkandreturn(512, 512, mlx->reload4) == -1)
		return (-1);
	mlx->reload5 = mlx_xpm_file_to_image(mlx->mlx, "./tet/reload4.xpm", &w, &h);
	if (checkandreturn(512, 512, mlx->reload5) == -1)
		return (-1);
	return (1);
}

void lol()
{
	system("leaks cub3D_bonus");
}

int	main(int ac, char **av)
{
	atexit(lol);
	t_strct	mlx;
	t_data	data;

	if (ac != 2)
		return (wrerror("invalid arguments"), 1);
	if (checkfilename(av[1]) == -1)
		return (1);
	init_data1(&mlx, &data);
	init_graphics(&mlx);
	if (initanimtex(&mlx) == -1)
		return (1);
	if (parsing(&data, &mlx, av[1]) == -1)
		return (exit_fn(&data), 1);
	if (checkifmapvalid(&data))
		return (exit_fn(&data) ,1);
	init_data2(&data);
	init_events(&mlx);
	mlx_loop_hook(mlx.mlx, render3d, &data);
	mlx_loop(mlx.mlx);
}
