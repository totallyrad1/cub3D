#include "../header.h"

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
		wrerror("invalid map\n");
		return (0);
	}
	if (map && i - 1 >= 0 && check0(map[i - 1][j]))
	{
		wrerror("invalid map\n");
		return (0);
	}
	if (map && map[i][j + 1] && check0(map[i][j + 1]))
	{
		wrerror("invalid map\n");
		return (0);
	}
	if (map && j - 1 >= 0 && check0(map[i][j - 1]))
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
		|| c == 'W')
		return (0);
	return (1);
}
