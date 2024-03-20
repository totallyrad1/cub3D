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
		wrerror("invalid map\n");
		return (0);
	}
	if (map && i - 1 >= 0 && check1(map[i - 1][j]))
	{
		wrerror("invalid map\n");
		return (0);
	}
	if (map && map[i][j + 1] && check1(map[i][j + 1]))
	{
		wrerror("invalid map\n");
		return (0);
	}
	if (map && j - 1 >= 0 && check1(map[i][j - 1]))
	{
		wrerror("invalid map\n");
		return (0);
	}
	return (1);
}

int check2(char **map, int i, int j)
{
	if (map && !map[i + 1])
	{
		wrerror("invalid map\n");
		return (0);
	}
	if (map && i - 1 < 0)
	{
		wrerror("invalid map\n");
		return (0);
	}
	if (map && !map[i][j + 1])
	{
		wrerror("invalid map\n");
		return (0);
	}
	if (map && j - 1 < 0)
	{
		wrerror("invalid map\n");
		return (0);
	}
	return (1);
}

int playerchar_found(char c)
{
	if(c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	checkifmapvalid(char **map)
{
	int	i;
	int	j;
	int count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ' && !check(map, i , j))
				return (1);
			if (map[i][j] == '0' && !check2(map, i, j))
				return (1);
			if (playerchar_found(map[i][j]))
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		return (wrerror("less or more than 1 player char found\n"), 1);
	return (0);
}
