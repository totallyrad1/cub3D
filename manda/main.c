/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:47:17 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/09 15:45:57 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_data1(t_strct *mlx, t_data *data)
{
	data->no = NULL;
	data->so = NULL;
	data->ea = NULL;
	data->we = NULL;
	data->walk = 0;
	data->turn = 0;
	data->left_right = 0;
	mlx->data = data;
	data->mlx = mlx;
	data->f_color = -1;
	data->c_color = -1;
	data->lc_tillstartofmap = 0;
}

void	init_data2(t_data *data)
{
	data->x = data->x * TILE_SIZE + TILE_SIZE / 2;
	data->y = data->y * TILE_SIZE + TILE_SIZE / 2;
	data->rotation_speed = 2 * (M_PI / 180);
}

t_ray	*ray_generator(t_data *data)
{
	t_ray	*rays = malloc(sizeof(t_ray) * WIDTH);
	if (!rays)
		exit(1);
	double angle = data->angle - (FOV / 2);
	float res = FOV / WIDTH;
	for (int i = 0; i < WIDTH; i++)
	{
		angle = normalize(angle);
		rays[i].angle = angle;
		rays[i].dis = cast(data, angle) * cos(angle - data->angle);
		rays[i].hitx = data->hhitx;
		rays[i].hity = data->hhity;
		rays[i].ver = data->ver;
		rays[i].wallprjct = (TILE_SIZE / rays[i].dis) * DISPROJ;
		angle += res;
	}
	return (rays);
}

int	is_ok(t_data *data, int x, int y)
{
	int a;

	a = MOVE_SPEED;
	if (data->mp[y / TILE_SIZE][x / TILE_SIZE] == '1')
		return (0);
	if (data->mp[(y + a)  / TILE_SIZE][x / TILE_SIZE] == '1'
		|| data->mp[y  / TILE_SIZE][(x + a) / TILE_SIZE] == '1'
		|| data->mp[(y - a)  / TILE_SIZE][x / TILE_SIZE] == '1'
		|| data->mp[y  / TILE_SIZE][(x - a) / TILE_SIZE] == '1')
		return (0);
	return (1);
}

void	update(t_data *data)
{
	double	xx;
	double	yy;

	data->angle = normalize(data->angle);
	xx = cos(data->angle) * (MOVE_SPEED);
	yy = sin(data->angle) * (MOVE_SPEED);
	if (data->walk && is_ok(data, data->x + data->walk * xx, data->y + data->walk * yy))
	{
		data->x += data->walk * xx;
		data->y += data->walk * yy;
	}
	if (data->left_right && is_ok(data, data->x + data->left_right * yy, data->y - data->left_right * xx))
	{
		data->x += data->left_right * yy;
		data->y -= data->left_right * xx;
	}
	data->angle += data->turn * data->rotation_speed;
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

unsigned int	getpixelcolor(char *tex, int texOffset)
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
		if (rays[i].ver)
			return (mlx->data->ea);
		else
			return (mlx->data->so);
	else if (rays[i].angle >= S && rays[i].angle <= W)
		if (rays[i].ver)
			return (mlx->data->we);
		else
			return (mlx->data->so);
	else if (rays[i].angle >= W && rays[i].angle <= N)
		if (rays[i].ver)
			return (mlx->data->we);
		else
			return (mlx->data->no);
	else
		if (rays[i].ver)
			return (mlx->data->ea);
		else
			return (mlx->data->no);
}

void	setvalues(t_vars *vars, t_ray *rays, t_strct *mlx, int i)
{
	vars->tex = mlx_get_data_addr(getwalltexture(rays, mlx, i), &vars->b, &vars->l, &vars->x);
    vars->projwallheight = (TILE_SIZE / rays[i].dis) * DISPROJ;
	vars->wallheight = (int)vars->projwallheight;
	vars->wtoppixel = (HEIGHT / 2) - (vars->wallheight / 2);
	if (vars->wtoppixel < 0)
		vars->wtoppixel = 0;
	vars->wbpotpixel = (HEIGHT / 2) + (vars->wallheight / 2);
	if (vars->wbpotpixel > HEIGHT)
		vars->wbpotpixel = HEIGHT;
	if (rays[i].ver)
		vars->texX = (int)rays[i].hity % TILE_SIZE;
	else
		vars->texX = (int)rays[i].hitx % TILE_SIZE;
	vars->j = 0;
}

void	walls(t_ray *rays, t_strct *mlx)
{
	t_data	*d;
	t_vars	vars;

	d = mlx->data;
	vars.i = 0;
	while (vars.i < WIDTH)
	{
		setvalues(&vars, rays, mlx, vars.i);
		while (vars.j < HEIGHT)
		{
			if (vars.j > (HEIGHT / 2 - rays[vars.i].wallprjct / 2) && vars.j < (HEIGHT / 2 + rays[vars.i].wallprjct / 2))
			{
				vars.disfromtop = vars.j + (vars.wallheight / 2) - (HEIGHT / 2);
				vars.texY = vars.disfromtop * ((float)TILE_SIZE / vars.wallheight);
				vars.color = getpixelcolor(vars.tex, (TILE_SIZE * vars.texY + vars.texX) * (vars.b / 8));
				pixel_put(mlx, vars.i, vars.j, vars.color);
			}	
			if (((vars.i - WIDTH / 2) * (vars.i - WIDTH / 2) + (vars.j - HEIGHT / 2) * (vars.j - HEIGHT / 2)) < 10)
				pixel_put(mlx, vars.i, vars.j, 0x000000);
			vars.j++;
		}
		vars.i++;
	}
}

int	render3d(void *ptr)
{
	t_data *data;
	t_strct	*mlx;
	t_ray	*rays;

	data = ptr;
	mlx = data->mlx;
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
		exit(1);								//free the map
	mlx->bf = mlx_get_data_addr(mlx->img, &mlx->pxl_b, &mlx->ln_b, &mlx->en);
	if (!mlx->bf)
		exit(1);
	update(data);
	rays = ray_generator(data);
	floor_ceiling(mlx, data);
	walls(rays, mlx);
	free(rays);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}

int main(int ac, char **av)
{
	t_strct	mlx;
	t_data data;

	if (ac != 2)
		return(wrerror("invalid arguments"), 1);
	if (checkfilename(av[1]) == -1)
		return (1);
	init_data1(&mlx, &data);
	init_graphics(&mlx);
	if(parsing(&data, &mlx, av[1]) == -1)
		return (1);
	if(checkifmapvalid(&data))
		return (1);
	init_data2(&data);
	init_events(&mlx);
	mlx_loop_hook(mlx.mlx, render3d, &data);
	mlx_loop(mlx.mlx);
}
