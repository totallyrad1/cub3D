/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:46:59 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/10 15:56:52 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void	init_graphics(t_strct *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		exit(1);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!mlx->win)
		exit(1);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
		exit(1);
	mlx->bf = mlx_get_data_addr(mlx->img, &mlx->pxl_b, &mlx->ln_b, &mlx->en);
	if (!mlx->bf)
		exit(1);
	mlx->texid = 0;
	mlx->anim1 = NULL;
	mlx->anim2 = NULL;
	mlx->anim3 = NULL;
	mlx->anim4 = NULL;
	mlx->reload1 = NULL;
	mlx->reload2 = NULL;
	mlx->reload3 = NULL;
	mlx->reload4 = NULL;
	mlx->reload5 = NULL;
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	keyclick_func(t_data *data, int ky)
{
	if (ky == 15 && data->amo)
	{
		data->texid = -25;
		data->amo = 0;
	}
	else if (ky == 12)
	{
		if (!data->hide)
		{
			mlx_mouse_show();
			data->hide = 1;
		}
		else
		{
			mlx_mouse_hide();
			mlx_mouse_move(data->mlx->win,
				(data->angle / 0.009696273622) + WIDTH / 2, HEIGHT / 2);
			data->hide = 0;
		}
	}
	else if (ky == 35)
		data->map = !data->map;
	return (0);
}

int	keyclick(int ky, void *ptr)
{
	t_strct	*mlx;
	t_data	*data;

	mlx = ptr;
	data = mlx->data;
	if (ky == KEY_ESC)
		destroy(mlx);
	else if ((ky == UP_KEY || ky == 126))
		data->walk = 1;
	else if ((ky == DOWN_KEY || ky == 125))
		data->walk = -1;
	else if (ky == LEFT_KEY)
		data->left_right = 1;
	else if (ky == RIGHT_KEY)
		data->left_right = -1;
	else if (ky == RRIGHT_KEY)
		data->turn = -1;
	else if (ky == RLEFT_KEY)
		data->turn = 1;
	else
		keyclick_func(data, ky);
	return (0);
}

int	keyrelease(int ky, void *ptr)
{
	t_data	*data;

	data = ptr;
	if (ky == UP_KEY || ky == 126 || ky == DOWN_KEY || ky == 125)
		data->walk = 0;
	else if (ky == LEFT_KEY || ky == RIGHT_KEY)
		data->left_right = 0;
	else if (ky == RRIGHT_KEY || ky == RLEFT_KEY)
		data->turn = 0;
	return (0);
}
