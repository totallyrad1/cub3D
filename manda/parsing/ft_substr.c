#include "../header.h"

int	ft_isspace(char c)
{
	if (c == 32 || c == '\t')
		return (1);
	if (c >= 9 && c <= 13)
		return (1);
	return (0);
}
