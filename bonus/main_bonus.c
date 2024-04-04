/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:47:17 by mozennou          #+#    #+#             */
/*   Updated: 2024/04/04 00:56:28 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

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
	data->hide = 1;
	data->scope = 0;
	data->f_color = -1;
	data->c_color = -1;
	data->amo = 0;
	data->lc_tillstartofmap = 0;
	data->texid = 0;
	mlx->texid1 = 0;
}

void	init_data2(t_data *data)
{
	data->x = data->x * TILE_SIZE + TILE_SIZE / 2;
	data->y = data->y * TILE_SIZE + TILE_SIZE / 2;
	data->move_speed = 3;
	data->rotation_speed = 2 * (M_PI / 180);
}

t_ray	*ray_generator(t_data *data)
{
	t_ray	*rays = malloc(sizeof(t_ray) * WIDTH);
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

	a = data->move_speed;
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
	int	xx;
	int	yy;

	xx = cos(data->angle) * (data->move_speed - data->scope * data->move_speed / 2);
	yy = sin(data->angle) * (data->move_speed - data->scope * data->move_speed / 2);
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
	data->angle += data->turn * data->rotation_speed * data->hide;
	if (data->turn && !data->hide)
		mlx_mouse_move(data->mlx->win, (int)((data->angle /((M_PI / 180) / 1.8)) + WIDTH / 2) % WIDTH, HEIGHT / 2);
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
			if (j > HEIGHT / 2)
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

void *getanimetex(t_strct *mlx)
{
	if(mlx->texid1 < 10)
		return (mlx->kirby1);
	else if(mlx->texid1 < 20)
		return (mlx->kirby2);
	else if(mlx->texid1 < 30)
		return (mlx->kirby3);
	else if(mlx->texid1 < 40)
		return (mlx->kirby4);
	else if(mlx->texid1 < 50)
		return (mlx->kirby5);
	else if(mlx->texid1 < 60)
		return (mlx->kirby6);
	else
		return (mlx->kirby7);
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
	// vars->animtex = mlx_get_data_addr(getanimetex(mlx), &vars->b1, &vars->l1, &vars->x1);
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
				vars.color = getpixelcolor(vars.tex, vars.b, (TILE_SIZE * vars.texY + vars.texX) * (vars.b / 8));
				pixel_put(mlx, vars.i, vars.j, vars.color);
			}
			// if (vars.j % 2 == 0 && vars.j > (HEIGHT / 2 - rays[vars.i].wallprjct / 2) && vars.j < (HEIGHT / 2 + rays[vars.i].wallprjct / 2))
			// {
			// 	vars.disfromtop = vars.j + (vars.wallheight / 2) - (HEIGHT / 2);
			// 	vars.texY = vars.disfromtop * ((float)TILE_SIZE / vars.wallheight);
			// 	vars.color = getpixelcolor(vars.animtex, vars.b1, (TILE_SIZE * vars.texY + vars.texX) * (vars.b1 / 8));
			// 	pixel_put(mlx, vars.i, vars.j, vars.color);
			// }
			if (((vars.i - WIDTH / 2) * (vars.i - WIDTH / 2) + (vars.j - HEIGHT / 2) * (vars.j - HEIGHT / 2)) < 10)
				pixel_put(mlx, vars.i, vars.j, 0x000000);
			vars.j++;
		}
		vars.i++;
	}
}

void drawarm(t_data *data , t_strct *mlx)
{
	if(data->texid >= 0)
	{
		if(data->texid < 3)
			mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->anim1, WIDTH / 2 - 150, HEIGHT / 2);
		else if (data->texid < 5)
			mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->anim2, WIDTH / 2 - 150, HEIGHT / 2);
		else if (data->texid < 8)
			mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->anim3, WIDTH / 2 - 150, HEIGHT / 2);
		else if (data->texid < 13)
			mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->anim4, WIDTH / 2 - 150, HEIGHT / 2);
	}
	else
	{
		if(data->texid > -5)
			mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->reload1, WIDTH / 2 - 150, HEIGHT / 2);
		else if (data->texid > -10)
			mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->reload2, WIDTH / 2 - 150, HEIGHT / 2);
		else if (data->texid > -15)
			mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->reload3, WIDTH / 2 - 150, HEIGHT / 2);
		else if (data->texid > -20)
			mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->reload4, WIDTH / 2 - 150, HEIGHT / 2);
		else if (data->texid > -25)
			mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->reload5, WIDTH / 2 - 150, HEIGHT / 2);
	}
		
}

int	render3d(void *ptr)
{
	t_data *data;
	t_strct	*mlx;
	t_ray	*rays;

	data = ptr;
	mlx = data->mlx;
	if (data->texid > 0)
		data->texid--;
	if (data->texid <= 0)
		data->texid++;
	if(mlx->texid1 > 70)
		mlx->texid1 = 0;
	mlx->texid1++;
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
		exit(1);								//free the map
	mlx->bf = mlx_get_data_addr(mlx->img, &mlx->pxl_b, &mlx->ln_b, &mlx->endian);
	if (!mlx->bf)
		exit(1);
	update(data);
	rays = ray_generator(data);
	floor_ceiling(mlx, data);
	walls(rays, mlx);
	// if (data->scope)
	// 	draw_scope(mlx);
	if (data->map)
		draw_map(mlx, data);
	else
	{
		mini_map(mlx, data);
		draw_amo(mlx, 8 - data->amo);
	}
	free(rays);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	if(!data->map)
		drawarm(data, mlx);
	return (0);
}

int initanimtex(t_strct *mlx)
{
	int w;
	int h;
	
	mlx->anim1 = mlx_xpm_file_to_image(mlx->mlx, "./tet/shoot1.xpm", &w, &h);
	if (checkandreturn(64, 64, mlx->anim1) == -1)
		return (-1);
	mlx->anim2 = mlx_xpm_file_to_image(mlx->mlx, "./tet/shoot3.xpm", &w, &h);
	if (checkandreturn(64, 64, mlx->anim2) == -1)
		return (-1);
	mlx->anim3 = mlx_xpm_file_to_image(mlx->mlx, "./tet/shoot4.xpm", &w, &h);
	if (checkandreturn(64, 64, mlx->anim3) == -1)
		return (-1);
	mlx->anim4 = mlx_xpm_file_to_image(mlx->mlx, "./tet/shoot5.xpm", &w, &h);
	if (checkandreturn(64, 64, mlx->anim4) == -1)
		return (-1);
	mlx->reload1 = mlx_xpm_file_to_image(mlx->mlx, "./tet/reload0.xpm", &w, &h);
	if (checkandreturn(64, 64, mlx->reload1) == -1)
		return (-1);
	mlx->reload2 = mlx_xpm_file_to_image(mlx->mlx, "./tet/reload1.xpm", &w, &h);
	if (checkandreturn(64, 64, mlx->reload2) == -1)
		return (-1);
	mlx->reload3 = mlx_xpm_file_to_image(mlx->mlx, "./tet/reload2.xpm", &w, &h);
	if (checkandreturn(64, 64, mlx->reload3) == -1)
		return (-1);
	mlx->reload4 = mlx_xpm_file_to_image(mlx->mlx, "./tet/reload3.xpm", &w, &h);
	if (checkandreturn(64, 64, mlx->reload4) == -1)
		return (-1);
	mlx->reload5 = mlx_xpm_file_to_image(mlx->mlx, "./tet/reload4.xpm", &w, &h);
	if (checkandreturn(64, 64, mlx->reload5) == -1)
		return (-1);
	// mlx->kirby1 = mlx_xpm_file_to_image(mlx->mlx, "./bonus/tex/anim1.xpm", &w, &h);
	// if (checkandreturn(64, 64, mlx->kirby1) == -1)
	// 	return (-1);
	// mlx->kirby2 = mlx_xpm_file_to_image(mlx->mlx, "./bonus/tex/anim2.xpm", &w, &h);
	// if (checkandreturn(64, 64, mlx->kirby2) == -1)
	// 	return (-1);
	// mlx->kirby3 = mlx_xpm_file_to_image(mlx->mlx, "./bonus/tex/anim3.xpm", &w, &h);
	// if (checkandreturn(64, 64, mlx->kirby3) == -1)
	// 	return (-1);
	// mlx->kirby4 = mlx_xpm_file_to_image(mlx->mlx, "./bonus/tex/anim4.xpm", &w, &h);
	// if (checkandreturn(64, 64, mlx->kirby4) == -1)
	// 	return (-1);
	// mlx->kirby5 = mlx_xpm_file_to_image(mlx->mlx, "./bonus/tex/anim5.xpm", &w, &h);
	// if (checkandreturn(64, 64, mlx->kirby5) == -1)
	// 	return (-1);
	// mlx->kirby6 = mlx_xpm_file_to_image(mlx->mlx, "./bonus/tex/anim6.xpm", &w, &h);
	// if (checkandreturn(64, 64, mlx->kirby6) == -1)
	// 	return (-1);
	// mlx->kirby7 = mlx_xpm_file_to_image(mlx->mlx, "./bonus/tex/anim7.xpm", &w, &h);
	// if (checkandreturn(64, 64, mlx->kirby7) == -1)
	// 	return (-1);
	return (1);
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
	if (initanimtex(&mlx) == -1)
		return (1);
	if (parsing(&data, &mlx, av[1]) == -1)
		return (1);
	if (checkifmapvalid(&data))
		return (1);
	init_data2(&data);
	init_events(&mlx);
	mlx_loop_hook(mlx.mlx, render3d, &data);
	mlx_loop(mlx.mlx);
}
