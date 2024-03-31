/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:45:39 by mozennou          #+#    #+#             */
/*   Updated: 2024/03/31 00:09:04 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include "defines.h"
# include "./get_next_line/get_next_line.h"

typedef struct s_strct	t_strct;

typedef struct s_data
{
	int		x;
	int		y;
	float	angle;
	float	move_speed;
	float	rotation_speed;
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
	t_strct	*mlx;
	int		lc_tillstartofmap;
}			t_data;

typedef struct s_ray
{
	double	hitx;
	double	hity;
	double	dis;
	double	wallprjct;
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

int	checkifmapvalid(t_data *data);

#endif