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

int playerchar_found(char c, float *angle)
{
	if(c == 'N')
		return (*angle = N, 1);
	if( c == 'S')
		return (*angle = S, 1);
	if(c == 'E' )
		return (*angle = E, 1);
	if( c == 'W')
		return (*angle = W, 1);
	return (0);
}

int	checkifmapvalid(t_data *data)
{
	int	i;
	int	j;
	int count;

	i = 0;
	count = 0;
	while ((data)->map[i])
	{
		j = 0;
		while ((data)->map[i][j])
		{
			if ((data)->map[i][j] == ' ' && !check((data)->map, i , j))
				return (1);
			if ((data)->map[i][j] == '0' && !check2((data)->map, i, j))
				return (1);
			if (playerchar_found((data)->map[i][j], &(data->player.angle)))
			{
				data->player.x = i;
				data->player.y = j;
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		return (wrerror("less or more than 1 player char found\n"), 1);
	return (0);
}
