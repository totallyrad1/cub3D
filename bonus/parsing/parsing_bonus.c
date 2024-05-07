/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:47:45 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/07 15:58:30 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus.h"

char *linemodified(char *line, int longestline)
{
	char *newline = malloc(longestline + 1);
	int i = 0;
	while(i < longestline && line[i])
	{
		newline[i] = line[i];
		i++;
	}
	while(i < longestline)
		newline[i++] = ' ';
	newline[i] = '\0';
	free(line);
	return (newline);
}

void free_array(char **line)
{
	int	i;

	i = 0;
	if (line)
	{
		while(line[i])
			free(line[i++]);
		free(line);
	}
}

int	checkandreturn(int w, int h, void *img)
{
	if (img == NULL)
		return (wrerror("invalid texture size or path\n"), -1);
	return (0);
}

int	settextures_value(char *key, t_data **data, t_strct **mlx, char *value)
{
	int	w;
	int	h;

	if (!ft_strcmp(key, "SO") && !(*data)->so)
	{
		(*data)->so = mlx_xpm_file_to_image((*mlx)->mlx, value, &w, &h);
		return (checkandreturn(w, h, (*data)->so));
	}
	else if (!ft_strcmp(key, "EA") && !(*data)->ea)
	{
		(*data)->ea = mlx_xpm_file_to_image((*mlx)->mlx, value, &w, &h);
		return (checkandreturn(w, h, (*data)->ea));
	}
	else if (!ft_strcmp(key, "NO") && !(*data)->no)
	{
		(*data)->no = mlx_xpm_file_to_image((*mlx)->mlx, value, &w, &h);
		return (checkandreturn(w, h, (*data)->no));
	}
	else if (!ft_strcmp(key, "WE") && !(*data)->we)
	{
		(*data)->we = mlx_xpm_file_to_image((*mlx)->mlx, value, &w, &h);
		return (checkandreturn(w, h, (*data)->we));
	}
	else
		return (-1);
}

int checkvalues(int i1, int i2, int i3)
{
	if (i1 < 0 || i1 > 255)
		return (0);
	if (i2 < 0 || i2 > 255)
		return (0);
	if (i3 < 0 || i3 > 255)
		return (0);
	return (1);
}

int	to_color(int r, int g, int b)
{
	return (((r) << 16) | ((g) << 8) | (b));
}

int setcolors_value(char *key, char *value, t_data **data)
{
	int j;
	int	r;
	int	g;
	int	b;

	j = 0;
	printf("here\n");
	if(checkvalidnumbers(value) == 0)
		return (-1);
	if (!ft_strcmp(key, "C") && (*data)->c_color == -1)
	{
		r = ft_atoi(value, &j);
		g = ft_atoi(value, &j);
		b = ft_atoi(value, &j);
		printf("%d %d %d\n", r, g , b);
		if(!checkvalues(r, g, b))
			return (-1);
		return ((*data)->c_color = to_color(r, g, b), 1);
	}
	if (!ft_strcmp(key, "F") && (*data)->f_color == -1)
	{
		r = ft_atoi(value, &j);
		g = ft_atoi(value, &j);
		b = ft_atoi(value, &j);
		printf("%d %d %d\n", r, g , b);
		if(!checkvalues(r, g, b))
			return (-1);
		return ((*data)->f_color = to_color(r, g, b), 1);
	}
	return ( -1);
}
