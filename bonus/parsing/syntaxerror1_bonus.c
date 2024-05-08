/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:48:03 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/08 15:44:10 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus.h"

int	checkfilename(char *filename)
{
	int	len;
	int	fd;

	if (!filename)
		return (wrerror("invalid filename"), -1);
	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(&filename[len - 4], ".cub"))
		return (wrerror("invalid filename"), -1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (wrerror("cant open fd\n"), -1);
	close(fd);
	return (1);
}

int	check0(char c)
{
	if (c != ' ' && c != '1' && c != '\n' && c != '\0')
		return (1);
	return (0);
}

int	check1(char **map, int i, int j)
{
	if (map && map[i + 1] && check0(map[i + 1][j]))
	{
		wrerror("invalid map5\n");
		return (0);
	}
	if (map && i - 1 >= 0 && check0(map[i - 1][j]))
	{
		wrerror("invalid map6\n");
		return (0);
	}
	if (map && map[i][j + 1] && check0(map[i][j + 1]))
	{
		wrerror("invalid map7\n");
		return (0);
	}
	if (map && j - 1 >= 0 && check0(map[i][j - 1]))
	{
		wrerror("invalid map8\n");
		return (0);
	}
	return (1);
}

int	check2(char **map, int i, int j)
{
	if (map && !map[i + 1])
	{
		wrerror("invalid map1\n");
		return (0);
	}
	if (map && i - 1 < 0)
	{
		wrerror("invalid map2\n");
		return (0);
	}
	if (map && !map[i][j + 1])
	{
		wrerror("invalid map3\n");
		return (0);
	}
	if (map && j - 1 < 0)
	{
		wrerror("invalid map4\n");
		return (0);
	}
	return (1);
}

int	playerchar_found(char c, float *angle)
{
	if (c == 'N')
		return (*angle = N, 1);
	if (c == 'S')
		return (*angle = S, 1);
	if (c == 'E' )
		return (*angle = E, 1);
	if (c == 'W')
		return (*angle = W, 1);
	return (0);
}
