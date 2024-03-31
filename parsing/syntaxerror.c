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

int	checkifmapvalid(t_data *data)
{
	int		i;
	int		j;
	int 	count;
	char	c;

	i = 0;
	count = 0;
	while ((data)->mp[i])
	{
		j = 0;
		while ((data)->mp[i][j])
		{
			c = (data)->mp[i][j];
			if (mapcharscheck(c))
				return (wrerror("invalid map\n"), 1);
			if (c == ' ' && !check1((data)->mp, i , j))
				return (1);
			if (c == '0' && !check2((data)->mp, i, j))
				return (1);
			if (playerchar_found(c, &(data->angle)))
			{
				data->x = j;
				data->y = i;
				count++;
				(data)->mp[i][j] = '0';
			}
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
