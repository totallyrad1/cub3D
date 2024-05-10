/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:56:04 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/10 14:34:24 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	setvalues(t_vars *vars, t_ray *rays, t_strct *mlx, int i)
{
	vars->tex = mlx_get_data_addr(getwalltexture(rays, mlx, i),
			&vars->b, &vars->l, &vars->x);
	vars->projwallheight = (TILE_SIZE / rays[i].dis) * DISPROJ;
	vars->wallheight = (int)vars->projwallheight;
	vars->wtoppixel = (HEIGHT / 2) - (vars->wallheight / 2);
	if (vars->wtoppixel < 0)
		vars->wtoppixel = 0;
	vars->wbpotpixel = (HEIGHT / 2) + (vars->wallheight / 2);
	if (vars->wbpotpixel > HEIGHT)
		vars->wbpotpixel = HEIGHT;
	if (rays[i].ver)
		vars->texx = (int)rays[i].hity % TILE_SIZE;
	else
		vars->texx = (int)rays[i].hitx % TILE_SIZE;
	vars->j = 0;
}

void	walls(t_ray *rays, t_strct *mlx)
{
	t_data			*d;
	t_vars			vars;
	static int		a = TILE_SIZE;

	d = mlx->data;
	floor_ceiling(mlx, d);
	vars.i = 0;
	while (vars.i < WIDTH)
	{
		setvalues(&vars, rays, mlx, vars.i);
		while (vars.j < HEIGHT)
		{
			if (vars.j > (HEIGHT / 2 - rays[vars.i].wallprjct / 2)
				&& vars.j < (HEIGHT / 2 + rays[vars.i].wallprjct / 2))
			{
				vars.disfromtop = vars.j + (vars.wallheight / 2) - (HEIGHT / 2);
				vars.texy = vars.disfromtop * ((float)a / vars.wallheight);
				vars.color = getpixelcolor(vars.tex,
						(a * vars.texy + vars.texx) * (vars.b / 8));
				pixel_put(mlx, vars.i, vars.j, vars.color);
			}
			vars.j++;
		}
		vars.i++;
	}
}

int	new_image(t_strct *mlx, t_data *data)
{
	if (data->texid > 0)
		data->texid--;
	if (data->texid <= 0)
		data->texid++;
	if (mlx->texid1 > 70)
		mlx->texid1 = 0;
	mlx->texid1++;
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
		return (free(data->mp), exit(1), 1);
	mlx->bf = mlx_get_data_addr(mlx->img, &mlx->pxl_b, &mlx->ln_b,
			&mlx->en);
	if (!mlx->bf)
		return (free(data->mp), exit(1), 1);
	return (0);
}

int	render3d(void *ptr)
{
	t_data	*data;
	t_strct	*mlx;
	t_ray	*rays;

	data = ptr;
	mlx = data->mlx;
	new_image(mlx, data);
	rays = ray_generator(data);
	walls(rays, mlx);
	free(rays);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}
