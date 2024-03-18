/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:37:02 by mozennou          #+#    #+#             */
/*   Updated: 2024/03/18 14:35:59 by asnaji           ###   ########.fr       */
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
# include "defines.h"
# include "./get_next_line/get_next_line.h"

typedef struct s_strct
{
	void	*mlx;
	void	*img;
	void	*win;
}	t_strct;

typedef struct s_img
{
	char	*bf;
	int		pxl_b;
	int		ln_b;
	int		endian;
}	t_img;

typedef struct s_data
{
	char **map;
}			t_data;

void	init_graphics(t_strct *mlx);
void	init_events(t_strct *mlx);
int		keyclick(int key, void *ptr);
void	wrerror(char *str);
char **newmapfn();
int	checkifmapvalid(char **map);

#endif