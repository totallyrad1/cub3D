#include "../header.h"

int checkfilename(char *filename)
{
	int	len;

	if (!filename)
		return (wrerror("invalid filename"), -1);
	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(&filename[len - 4], ".cub"))
		return (wrerror("invalid filename"), -1);
	return (1);
}