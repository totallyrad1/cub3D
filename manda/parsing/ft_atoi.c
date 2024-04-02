#include "../header.h"

int ft_atoi(char *str, int *j)
{
	int res;

	res = 0;
	while (str[*j] && (str[*j] >= '0' && str[*j] <= '9'))
	{
		res = res * 10 + (str[*j] - '0');
		(*j)++;
	}
	if (str[*j] == ',')
		(*j)++;
	while(str[*j] && ft_isspace(str[*j]))
			(*j)++;
	return (res);
}