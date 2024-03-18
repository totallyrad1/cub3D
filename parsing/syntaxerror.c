/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:34:00 by asnaji            #+#    #+#             */
/*   Updated: 2024/03/18 14:53:13 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int check1(char c)
{
	if (c != ' ' && c != '1' && c != '\n' && c != '\0')
		return (1);
	return (0);
}

int check(char **map, int i, int j)
{
	if (map && map[i + 1] && check1(map[i + 1][j]))
	{
		wrerror("invalid map1\n");
		return (0);
	}
	if (map && i - 1 >= 0 && check1(map[i - 1][j]))
	{
		wrerror("invalid map2\n");
		return (0);
	}
	if (map && map[i][j + 1] && check1(map[i][j + 1]))
	{
		wrerror("invalid map3\n");
		return (0);
	}
	if (map && j - 1 >= 0 && check1(map[i][j - 1]))
	{
		wrerror("invalid map4\n");
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

int	checkifmapvalid(char **map)
{
	int	i;
	int	j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == ' ' && !check(map, i , j))
			{
				printf("%d\n%d\n", i , j);
				return (1);
			}
			if(map[i][j] == '0' && !check2(map, i, j))
			{
				printf("%d\n%d\n", i , j);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
