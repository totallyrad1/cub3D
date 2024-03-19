#include "../header.h"

void	wrerror(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
}
