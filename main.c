#include "header.h"

int main(int ac, char **av)
{
	t_strct	mlx;
	t_data data;

	if (ac != 2)
		return(wrerror("invalid arguments"), 1);
	if (checkfilename(av[1]) == -1)
		return (1);
	init_graphics(&mlx);
	data.NO = NULL;
	data.SO = NULL;
	data.EA = NULL;
	data.WE = NULL;
	if(parse_everything(&data, &mlx, av[1]) == -1)
		return (1);
	if(checkifmapvalid(data.map))
		return (1);
	init_events(&mlx);
	mlx_loop(mlx.mlx);
}
