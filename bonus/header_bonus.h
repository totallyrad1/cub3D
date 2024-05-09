/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:45:39 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/09 19:48:46 by asnaji           ###   ########.fr       */
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
	double	x;
	double	y;
	double	angle;
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
	void	*door;
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
	int		hdoor;
	int		vdoor;
}			t_data;

typedef struct s_ray
{
	double	hitx;
	double	hity;
	double	dis;
	int		ver;
	int		door;
	double	wallprjct;
	double	angle;
}	t_ray;

typedef struct s_strct
{
	void	*mlx;
	void	*img;
	void	*win;
	char	*bf;
	int		pxl_b;
	int		ln_b;
	int		en;
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

typedef struct s_4points
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
}	t_4points;

void			vinter(t_data *data, double *xinter, double *yinter,
					double angle);
int				settextures_value(char *key, t_data **data, t_strct **mlx,
					char *value);
int				fill_forkey(t_data **data, char *key, char *value,
					t_strct **mlx);
void			vstep(t_data *data, double *xstep, double *ystep, double angle);
void			init_graphics(t_strct *mlx);
void			init_events(t_strct *mlx);
int				keyclick(int key, void *ptr);
void			wrerror(char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_atoi(char *str, int *j);
int				checkfilename(char *filename);
void			pixel_put(t_strct *mlx, int x, int y, int color);
void			free_map(char **map);
int				destroy(t_strct *mlx);
double			cast(t_data *data, double angle);
double			normalize(double angle);
double			dis(double x1, double y1, double x2, double y2);
void			direction(double angle, int *up, int *right);
int				ft_isspace(char c);
int				setcolors_value(char *key, char *value, t_data **data);
char			*linemodified(char *line, int longestline);
int				parsing(t_data *data, t_strct *mlx, char *filename);
int				get_map(t_data **data, char *filename, int fd);
int				checkifmapvalid(t_data *data);
int				is_wall(t_data *data, double xx, double yy);
void			mini_map(t_strct *mlx, t_data *data);
int				gun_sound(char *s);
void			draw_amo(t_strct *mlx, int amo);
int				checkvalidnumbers(char *str);
void			draw_map(t_strct *mlx, t_data *data);
int				checkandreturn(int w, int h, void *img);
void			init_data1(t_strct *mlx, t_data *data);
void			init_data2(t_data *data);
t_ray			*ray_generator(t_data *data);
int				is_ok(t_data *data, int x, int y);
void			update(t_data *data);
void			floor_ceiling(t_strct *mlx, t_data *data);
unsigned int	getpixelcolor(char *tex, int texOffset);
void			*getwalltexture(t_ray *rays, t_strct *mlx, int i);
void			*getanimetex(t_strct *mlx);
void			setvalues(t_vars *vars, t_ray *rays, t_strct *mlx, int i);
void			drawarm(t_data *data, t_strct *mlx);
void			walls(t_ray *rays, t_strct *mlx);
void			direction_line(t_4points *p, t_strct *mlx);
int				render3d(void *ptr);
double			hcast(t_data *data, double angle, double xstep, double ystep);
double			vcast(t_data *data, double angle, double xstep, double ystep);
int				keyrelease(int ky, void *ptr);

int				parse_clrs_txtrs(t_data **data, t_strct **mlx, int fd);
void			fillkey_value(char *line, char **key, char **value);
int				check_that(t_data *data);

int				checkvalues(int i1, int i2, int i3);
int				to_color(int r, int g, int b);
void			free_array(char **line);

int				playerchar_found(char c, float *angle);
int				check2(char **map, int i, int j);
int				check1(char **map, int i, int j);
int				check0(char c);

void			exit_fn(t_data *data);

void			draw_reload(t_data *data, t_strct *mlx);
void			draw_shoot(t_data *data, t_strct *mlx);
#endif