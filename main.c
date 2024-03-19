
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

void	render(char **map, t_strct	*mlx)
{
	int player_x = 0;
	int player_y = 0;
	t_img	img;

	img.bf = mlx_get_data_addr(mlx->img, &img.pxl_b, &img.ln_b, &img.endian);
	int	wlen = WIDTH / strlen(map[0]), hlen = HEIGHT / len(map);
	printf("%d %d\n", wlen, hlen);
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (map[j / hlen][i / wlen] == '1' || (j % hlen) == 0 ||(i % wlen) == 0)
				pixel_put(&img, i, j, 0x00AAAA);
		}
	}
	for (int i = 0; i < WIDTH / wlen; i++)
	{
		for (int j = 0; j < HEIGHT / hlen; j++)
		{
			if (map[j][i] == 'P')
			{
				player_x = j;
				player_y = i;
				for (int m = -2; m < 2; m++)
				{
					for (int n = -2; n < 2; n++)
					{
						pixel_put(&img, i * wlen + wlen/2 + n + m, j * hlen + hlen/2 + m + n, 0xFF0000);
						pixel_put(&img, i * wlen + wlen/2 + n, j * hlen + hlen/2 + m, 0xFF0000);
						pixel_put(&img, i * wlen + wlen/2 + m, j * hlen + hlen/2 + n, 0xFF0000);
						pixel_put(&img, i * wlen + wlen/2 + n + m, j * hlen + hlen/2 + m + n, 0xFF0000);
					}
				}
			}
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int main()
{
	t_strct	mlx;

	init_graphics(&mlx);
	init_events(&mlx);
	char **map = newmapfn();
	for (int i = 0; map[i]; i++)
	{
		printf("%s\n", map[i]);
	}
	render(map, &mlx);
	mlx_loop(mlx.mlx);
}
