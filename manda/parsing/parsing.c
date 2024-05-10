/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:47:45 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/10 14:19:43 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*linemodified(char *line, int longestline)
{
	char	*newline;
	int		i;

	i = 0;
	newline = malloc(longestline + 1);
	if (!newline)
		exit(1);
	while (i < longestline && line[i])
	{
		newline[i] = line[i];
		i++;
	}
	while (i < longestline)
		newline[i++] = ' ';
	newline[i] = '\0';
	free(line);
	return (newline);
}

int	checkandreturn(int w, int h, void *img)
{
	if (img == NULL || w != 512 || h != 512)
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

void	set_rgb(int *r, int *g, int *b, char *value)
{
	int	j;

	j = 0;
	*r = ft_atoi(value, &j);
	*g = ft_atoi(value, &j);
	*b = ft_atoi(value, &j);
}

int	setcolors_value(char *key, char *value, t_data **data)
{
	int	r;
	int	g;
	int	b;

	if (checkvalidnumbers(value) == 0)
		return (-1);
	if (!ft_strcmp(key, "C") && (*data)->c_color == -1)
	{
		set_rgb(&r, &g, &b, value);
		if (!checkvalues(r, g, b))
			return (-1);
		return ((*data)->c_color = to_color(r, g, b), 1);
	}
	if (!ft_strcmp(key, "F") && (*data)->f_color == -1)
	{
		set_rgb(&r, &g, &b, value);
		if (!checkvalues(r, g, b))
			return (-1);
		return ((*data)->f_color = to_color(r, g, b), 1);
	}
	return (-1);
}
