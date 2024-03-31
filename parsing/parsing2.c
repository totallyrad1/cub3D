#include "../header.h"

int fill_forkey(t_data **data, char *key, char *value, t_strct **mlx)
{
	printf("[%s] [%s]\n", key, value);
	if (!ft_strcmp(key, "SO"))
		return (settextures_value(key, data, mlx, value));
	if (!ft_strcmp(key, "EA"))
		return (settextures_value(key, data, mlx, value));
	if (!ft_strcmp(key, "NO"))
		return (settextures_value(key, data, mlx, value));
	if (!ft_strcmp(key, "WE"))
		return (settextures_value(key, data, mlx, value));
	if (!ft_strcmp(key, "C"))
		return (setcolors_value(key, value, data));
	if (!ft_strcmp(key, "F"))
		return (setcolors_value(key, value, data));
	return (-1);
}

int fillandcheckmap(t_data **data, char *filename, int longestline)
{
	int fd;
	char *line;
	int i;
	
	i = 0;	
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (wrerror("error opening file\n"), free((*data)->mp), -1);
	while((*data)->lc_tillstartofmap-- > 0)
		free(get_next_line(fd));
	i = 0;
	line = get_next_line(fd);
	while((*data)->mp[i] && line)
	{
		(*data)->mp[i] = linemodified(line, longestline);
		line = get_next_line(fd);
		i++;
	}
	(*data)->mp[i] = NULL;
	close(fd);
	return (1);
}

int get_map(t_data **data, char *filename, int fd)
{
	char	*line;
	int		arr_size;
	int		longestline;

	arr_size = 0;
	line = get_next_line(fd);
	if(line == NULL)
		return (-1);
	longestline = 0;
	while(line)
	{
		if((int)ft_strlen(line) > longestline)
			longestline = (int)ft_strlen(line);
		arr_size++;
		free(line);
		line = get_next_line(fd);
	}
	(*data)->mp = malloc(sizeof(char *) * (arr_size + 1));
	if (!(*data)->mp)
		return (close(fd), -1);
	(*data)->mp[arr_size] = NULL;
	close(fd);
	return (fillandcheckmap(data, filename, longestline));
}
