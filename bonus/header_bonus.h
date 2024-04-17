/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:45:39 by mozennou          #+#    #+#             */
/*   Updated: 2024/04/04 00:50:21 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_BONUS_H
# define HEADER_BONUS_H

# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include "defines_bonus.h"
# include "./get_next_line/get_next_line_bonus.h"

typedef struct s_strct	t_strct;

typedef struct s_data
{
	int		x;
	int		y;
	double	angle;
	double	move_speed;
	double	rotation_speed;
	int		walk;
	int		left_right;
	int		turn;
	char	**mp;
	int		hhitx;
	int		hhity;
	int		vhitx;
	int		vhity;
	void	*so;
	void	*ea;
	void	*we;
	void	*no;
	int		f_color;
	int		c_color;
	int		up;
	int		right;
	int		i;
	int		j;
	int		ver;
	double	old_angle;
	t_strct	*mlx;
	int		amo;
	int		map;
	int		hide;
	int		lc_tillstartofmap;
	int		texid;
}			t_data;

typedef struct s_ray
{
	double	hitx;
	double	hity;
	double	dis;
	int		ver;
	double	wallprjct;
	double angle;
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
	void	*anim1;
	void	*anim2;
	void	*anim3;
	void	*anim4;
	void	*reload1;
	void	*reload2;
	void	*reload3;
	void	*reload4;
	void	*reload5;
	void	*kirby1;
	void	*kirby2;
	void	*kirby3;
	void	*kirby4;
	void	*kirby5;
	void	*kirby6;
	void	*kirby7;
	int		texid1;
	int		texid;
	t_data	*data;
}	t_strct;

typedef struct s_vars
{
	char	*tex;
	float	projwallheight;
	int		wallheight;
	int		wtoppixel;
	int		wbpotpixel;
	int		texX;
	int		texY;
	int		color;
	int		disfromtop;
	int		b;
	int		l;
	int		x;
	int		b1;
	int		l1;
	int		x1;
	int		i;
	int		j;
	char	*animtex;
}	t_vars;

void	init_graphics(t_strct *mlx);
void	init_events(t_strct *mlx);
int		keyclick(int key, void *ptr);
void	wrerror(char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(char *str, int *j);
int		checkfilename(char *filename);
void	pixel_put(t_strct *mlx, int x, int y, int color);
void	free_map(char **map);
int		destroy(t_strct *mlx);
double	cast(t_data *data, double angle);
double	normalize(double angle);
double	dis(double x1, double y1, double x2, double y2);
void	direction(double angle, int *up, int *right);
void	vinter(t_data *data, double *xinter, double *yinter, double angle);
void	vstep(t_data *data, double *xstep, double *ystep, double angle);

int	ft_isspace(char c);

int settextures_value(char *key, t_data **data, t_strct **mlx, char *value);
int setcolors_value(char *key, char *value, t_data **data);

char *linemodified(char *line, int longestline);

int parsing(t_data *data, t_strct *mlx, char *filename);

int get_map(t_data **data, char *filename, int fd);
int fill_forkey(t_data **data, char *key, char *value, t_strct **mlx);

int		checkifmapvalid(t_data *data);
int		is_wall(t_data *data, int x, int y);
void	mini_map(t_strct *mlx, t_data *data);
int	gun_sound(char *s);
void draw_amo(t_strct *mlx, int amo);
int checkvalidnumbers(char *str);
void	draw_map(t_strct *mlx, t_data *data);

int	checkandreturn(int w, int h, void *img);

#endif