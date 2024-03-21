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
	if ((fd = open(filename, O_RDWR)) == -1)
		return (wrerror("cant open fd\n"), -1);
	close(fd);
	return (1);
}

int validcharslist(char c)
{
	if(c == '\t')
		return (1);
	return (0);
}

int checkvalidchars(char *filename)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(filename, O_RDWR);
	if (fd == -1)
		return (wrerror("error opening file\n"), -1);
	line = get_next_line(fd);
	while(line)
	{
		i = 0;
		while(line && line[i])
		{
			if(validcharslist(line[i]))
				return (wrerror("tab found\n"), free(line), close(fd), -1);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
