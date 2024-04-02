#include "../header.h"

int	ft_isspace(char c)
{
	if (c == 32 || c == '\t')
		return (1);
	if (c >= 9 && c <= 13)
		return (1);
	return (0);
}

int	to_color(int r, int g, int b)
{
	return (((r) << 16) | ((g) << 8) | (b));
}

int	checkvalues(int i1, int i2, int i3)
{
	if (i1 < 0 || i1 > 255)
		return (0);
	if (i2 < 0 || i2 > 255)
		return (0);
	if (i3 < 0 || i3 > 255)
		return (0);
	return (1);
}

int	setcolors_value(char *key, char *value, t_data **data)
{
	int	j;
	int	r;
	int	g;
	int	b;

	j = 0;
	if (checknum(value) && !ft_strcmp(key, "C") && (*data)->c_color == -1)
	{
		r = ft_atoi(value, &j);
		g = ft_atoi(value, &j);
		b = ft_atoi(value, &j);
		if (!checkvalues(r, g, b))
			return (-1);
		return ((*data)->c_color = to_color(r, g, b), 1);
	}
	if (checknum(value) && !ft_strcmp(key, "F") && (*data)->f_color == -1)
	{
		r = ft_atoi(value, &j);
		g = ft_atoi(value, &j);
		b = ft_atoi(value, &j);
		if (!checkvalues(r, g, b))
			return (-1);
		return ((*data)->f_color = to_color(r, g, b), 1);
	}
	return ( -1);
}