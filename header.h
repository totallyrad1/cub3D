#ifndef HEADER_H
# define HEADER_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
#include <limits.h>
# include "defines.h"
# include "./get_next_line/get_next_line.h"

typedef struct s_strct t_strct;

typedef struct s_data
{
	int	    x;
    int	    y;
    float    angle;
    float    move_speed;
    float    rotation_speed;
	char	**mp;
	int		hhitx;
	int		hhity;
	int		vhitx;
	int		vhity;
	void	*SO;
	void	*EA;
	void	*WE;
	void	*NO;
	int		w;
	int		h;
	int		f_color;
	int		c_color;
	int		xlen;
	int		ylen;
	int		ver;
	t_strct	*mlx;
}			t_data;

typedef struct s_ray
{
	int	hitx;
	int	hity;
	int	dis;
	int	ver;
}	t_ray;


typedef struct s_strct
{
	void	*mlx;
	void	*img;
	void	*win;
	char	*bf;
	int		pxl_b;
	int		ln_b;
	int		endian;
	t_data	*data;
}	t_strct;

void	init_graphics(t_strct *mlx);
void	init_events(t_strct *mlx);
int		keyclick(int key, void *ptr);
void	wrerror(char *str);
void	render2(t_data *data, t_strct	*mlx);
int	checkifmapvalid(t_data *data);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
int ft_atoi(char *str, int *j);
int parse_everything(t_data *data, t_strct *mlx, char *filename);
int checkfilename(char *filename);
void	pixel_put(t_strct *mlx, int x, int y, int color);
int checkvalidchars(char *filename);

void	free_map(char **map);
int		destroy(t_strct *mlx);

int	render(void *ptr);
int		cast(t_data *data, double angle);
double	normalize(double angle);

#endif