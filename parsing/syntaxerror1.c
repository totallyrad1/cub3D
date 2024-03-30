#include "../header.h"

int checkfilename(char *filename)
{
	int	len;
	int	fd;

	if (!filename)
		return (wrerror("invalid filename"), -1);
	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(&filename[len - 4], ".cub"))
		return (wrerror("invalid filename"), -1);
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (wrerror("cant open fd\n"), -1);
	close(fd);
	return (1);
}
