/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:47:59 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/10 14:19:49 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	mapcharscheck(char c)
{
	if (c == ' ' || c == '0' || c == '1'
		|| c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == 'D')
		return (0);
	return (1);
}

int	door_check(int i, int j, char **map)
{
	if (i <= 0 || !map[i - 1] || !map[i - 1][j])
		return (-1);
	if (!map[i + 1] || !map[i + 1][j])
		return (-1);
	if (j <= 0 || !map[i] || !map[i][j - 1])
		return (-1);
	if (!map[i] || !map[i][j + 1])
		return (-1);
	if (map[i + 1][j] == '1' && map[i - 1][j] == '1'
		&& map[i][j + 1] == '0' && map[i][j - 1] == '0')
		return (1);
	if (map[i + 1][j] == '0' && map[i - 1][j] == '0'
		&& map[i][j + 1] == '1' && map[i][j - 1] == '1')
		return (1);
	return (-1);
}

int	checki_lmap_ajmi(t_data **data, int i, int j, int *count)
{
	float	t;
	char	c;

	c = (*data)->mp[i][j];
	if (mapcharscheck(c))
		return (wrerror("invalid map1\n"), 1);
	if (c == ' ' && !check1((*data)->mp, i, j))
		return (1);
	if ((c == '0' || playerchar_found(c, &t))
		&& !check2((*data)->mp, i, j))
		return (1);
	if (playerchar_found(c, &t))
	{
		(*data)->angle = t;
		(*data)->x = j;
		(*data)->y = i;
		(*count)++;
		(*data)->mp[i][j] = '0';
	}
	if ((*data)->mp[i][j] == 'D'
		&& door_check(i, j, (*data)->mp) == -1)
		return (wrerror("invalid door position\n"), 1);
	return (0);
}

int	checkifmapvalid(t_data *data)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while ((data)->mp[i])
	{
		j = 0;
		while ((data)->mp[i][j])
		{
			if (checki_lmap_ajmi(&data, i, j, &count))
				return (1);
			j++;
		}
		i++;
	}
	data->j = i * TILE_SIZE;
	data->i = j * TILE_SIZE;
	if (count != 1)
		return (wrerror("less or more than 1 player char found\n"), 1);
	return (0);
}
