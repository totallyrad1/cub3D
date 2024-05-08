/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:47:59 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/08 13:51:28 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus.h"

int check0(char c)
{
	if (c != ' ' && c != '1' && c != '\n' && c != '\0')
		return (1);
	return (0);
}

int check1(char **map, int i, int j)
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

int check2(char **map, int i, int j)
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

int playerchar_found(char c, float *angle)
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

int	mapcharscheck(char c)
{
	if (c == ' ' || c == '0' || c == '1'
		|| c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == 'D') // add D for the door
		return (0);
	return (1);
}

int door_check(int i, int j, char **map)
{
	if (i <= 0 || !map[i - 1] || !map[i - 1][j])
		return (wrerror("here 1\n"), -1);
	if (!map[i + 1] || !map[i + 1][j])
		return (wrerror("here 2\n"), -1);
	if (j <= 0 || !map[i] || !map[i][j - 1])
		return (wrerror("here 3\n"), -1);
	if (!map[i] || !map[i][j + 1])
		return (wrerror("here 4\n"), -1);
	if(map[i + 1][j] == '1' && map[i - 1][j] == '1' && map[i][j + 1] == '0' && map[i][j - 1] == '0')
		return (1);
	if(map[i + 1][j] == '0' && map[i - 1][j] == '0' && map[i][j + 1] == '1' && map[i][j - 1] == '1')
		return (1);
	return (wrerror("here 5\n"), -1);
}

int	checkifmapvalid(t_data *data)
{
	int		i;
	int		j;
	int 	count;
	char	c;
	float	t;

	i = 0;
	count = 0;
	while ((data)->mp[i])
	{
		j = 0;
		while ((data)->mp[i][j])
		{
			c = (data)->mp[i][j];
			if (mapcharscheck(c))
				return (wrerror("invalid map1\n"), 1);
			if (c == ' ' && !check1((data)->mp, i , j))
				return (1);
			if ((c == '0'  || playerchar_found(c, &t))&& !check2((data)->mp, i, j))
				return (1);
			if (playerchar_found(c, &t))
			{
				data->angle = t;
				data->x = j;
				data->y = i;
				count++;
				(data)->mp[i][j] = '0';
			}
			if ((data)->mp[i][j] == 'D' && door_check(i , j , (data)->mp) == -1)
				return (wrerror("invalid door position\n"), 1);
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
