#include "header.h"

#include <string.h>

int len(char **map)
{
	int i;
	for (i = 0; map[i]; i++)
	{
	}
	return (i);
}

void draw_player(t_data *data, t_strct	*mlx, t_img *img)
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (i <= data->player.y + 3 && j <= data->player.x + 3 && i > data->player.y - 3 && j > data->player.x - 3)
				pixel_put(img, i, j, 0xFF0000);
		}
	}
}

int in_line(int i, int j, t_data *data)
{
	int x1 = data->player.x, y1 = data->player.y, x2, y2, cross;
	float	ray_angle = data->player.angle - (FOV / 2);
	// for (int k = 0; k < 3; k++)
	// {
		x2 = data->hhitx;
		y2 = data->hhity;
		cross = (x2 - x1) * (i - y1) - (y2 - y1) * (j - x1);
		if (i <= (y2) && j <= (x2) && i >= y1 && j >= x1 && abs(cross) <= 100)
			return (1);
		else if (i >= (y2) && j >= (x2) && i <= y1 && j <= x1 && abs(cross) <= 100)
			return (1);
		else if (i >= (y2) && j <= (x2) && i <= y1 && j >= x1 && abs(cross) <= 100)
			return (1);
		else if (i <= (y2) && j >= (x2) && i >= y1 && j <= x1 && abs(cross) <= 100)
			return (1);
		// ray_angle += FOV / 2;
	// }
	return (0);
}

int in_line00(int i, int j, t_data *data)
{
	int x1 = data->player.x, y1 = data->player.y, x2, y2, cross;
	float	ray_angle = data->player.angle - (FOV / 2);
	// for (int k = 0; k < 3; k++)
	// {
		x2 = data->vhitx;
		y2 = data->vhity;
		cross = (x2 - x1) * (i - y1) - (y2 - y1) * (j - x1);
		if (i <= (y2) && j <= (x2) && i >= y1 && j >= x1 && abs(cross) <= 100)
			return (1);
		else if (i >= (y2) && j >= (x2) && i <= y1 && j <= x1 && abs(cross) <= 100)
			return (1);
		else if (i >= (y2) && j <= (x2) && i <= y1 && j >= x1 && abs(cross) <= 100)
			return (1);
		else if (i <= (y2) && j >= (x2) && i >= y1 && j <= x1 && abs(cross) <= 100)
			return (1);
		// ray_angle += FOV / 2;
	// }
	return (0);
}

int in_line1(int i, int j, t_data *data)
{
	int x1 = data->player.x, y1 = data->player.y, x2, y2, cross;
	float	ray_angle = data->player.angle - (FOV / 2);
	for (int k = 0; k < 3; k++)
	{
		x2 = data->player.x + sin(ray_angle) * 20;
		y2 = data->player.y + cos(ray_angle) * 20;
		cross = (x2 - x1) * (i - y1) - (y2 - y1) * (j - x1);
		if (i <= (y2) && j <= (x2) && i >= y1 && j >= x1 && abs(cross) <= 10)
			return (1);
		else if (i >= (y2) && j >= (x2) && i <= y1 && j <= x1 && abs(cross) <= 10)
			return (1);
		else if (i >= (y2) && j <= (x2) && i <= y1 && j >= x1 && abs(cross) <= 10)
			return (1);
		else if (i <= (y2) && j >= (x2) && i >= y1 && j <= x1 && abs(cross) <= 10)
			return (1);
		ray_angle += FOV / 2;
	}
	return (0);
}

void	render(t_data *data, t_strct	*mlx)
{
	int player_x = 0;
	int player_y = 0;
	t_img	img;

	img.bf = mlx_get_data_addr(mlx->img, &img.pxl_b, &img.ln_b, &img.endian);
	int	wlen = WIDTH / strlen(data->mp[0]) + 1, hlen = HEIGHT / len(data->mp) + 1;
	data->h = hlen;
	data->w = wlen;
	data->player.x = data->player.x * hlen + hlen / 2;
	data->player.y = data->player.y * wlen + wlen / 2;
	data->player.move_speed = 4;
	data->player.rotation_speed = 10 * (M_PI / 180);
	float	ray_angle = data->player.angle;
	cast(data, normalizeangle(ray_angle));
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (data->mp[j / hlen][i / wlen] == '1' || (j % hlen) == 0 ||(i % wlen) == 0)
				pixel_put(&img, i, j, 0x00AAFF);
			if (i <= data->player.y + 3 && j <= data->player.x + 3 && i > data->player.y - 3 && j > data->player.x - 3)
				pixel_put(&img, i, j, 0xFF0000);
			if (in_line1(i, j, data) || in_line(i, j, data) || in_line00(i, j, data))
			{
				pixel_put(&img, i, j, 0xFFFFFF);
			}
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	render2(t_data *data, t_strct	*mlx)
{
	int player_x = 0;
	int player_y = 0;
	t_img	img;

	img.bf = mlx_get_data_addr(mlx->img, &img.pxl_b, &img.ln_b, &img.endian);
	int	wlen = WIDTH / strlen(data->mp[0]) + 1, hlen = HEIGHT / len(data->mp) + 1;
	float	ray_angle = data->player.angle;
	cast(data, normalizeangle(ray_angle));
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (data->mp[j / hlen][i / wlen] == '1' || (j % hlen) == 0 ||(i % wlen) == 0)
				pixel_put(&img, i, j, 0x00AAFF);
			else
				pixel_put(&img, i, j, 0x000000);
			if (i <= data->player.y + 3 && j <= data->player.x + 3 && i > data->player.y - 3 && j > data->player.x - 3)
				pixel_put(&img, i, j, 0xFF0000);
			if (in_line1(i, j, data) || in_line(i, j, data) || in_line00(i, j, data))
				pixel_put(&img, i, j, 0xFFFFFF);
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	init_data1(t_strct *mlx, t_data *data)
{
	data->NO = NULL;
	data->SO = NULL;
	data->EA = NULL;
	data->WE = NULL;
	mlx->data = data;
}

int main(int ac, char **av)
{
	t_strct	mlx;
	t_data data;

	if (ac != 2)
		return(wrerror("invalid arguments"), 1);
	if (checkfilename(av[1]) == -1)
		return (1);
	if (checkvalidchars(av[1]) == -1)
		return (1);
	init_graphics(&mlx);
	init_data1(&mlx, &data);
	if(parse_everything(&data, &mlx, av[1]) == -1)
		return (1);
	if(checkifmapvalid(&data))
		return (1);
	init_events(&mlx);
	render(&data, &mlx);
	mlx_loop(mlx.mlx);
}
