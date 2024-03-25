#ifndef HEADER_H
# define HEADER_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "defines.h"
# include "./get_next_line/get_next_line.h"

typedef struct s_img
{
	char	*bf;
	int		pxl_b;
	int		ln_b;
	int		endian;
}	t_img;

typedef struct s_player
{
    int	    x;
    int	    y;
    float    angle;
    float    move_speed;
    float    rotation_speed;
}    t_player;

typedef struct s_data
{
	char	**mp;
	t_player    player;
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
}			t_data;

typedef struct s_strct
{
	void	*mlx;
	void	*img;
	void	*win;
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
void	pixel_put(t_img *data, int x, int y, int color);
int checkvalidchars(char *filename);

//ray_casting.c
double  normalizeangle(double angle);  //not used
int		cast(t_data *data, float angle);	//too


#endif