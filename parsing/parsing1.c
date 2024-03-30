#include "../header.h"

int check_that(t_data *data)
{
	if(data->so != NULL && data->ea != NULL && data->we != NULL && data->no != NULL && data->f_color != -1 && data->c_color != -1)
		return (1);
	return (0);
}

void fillkey_value(char *line, char **key, char **value)
{
	int	i;
	int tmp;

	i = 0;
	*key = NULL;
	*value = NULL;
	while (line[i] && ft_isspace(line[i]))
		i++;
	tmp = i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	*key = ft_substr(line, tmp, i);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i])
		*value = ft_substr(line, i, ft_strlen(line));
	else
		*value = NULL;
	if (line)
		free(line);
}

int parse_clrs_txtrs(t_data **data, t_strct **mlx, int fd)
{
	char *line;
	char *key;
	char *value;

	line = get_next_line(fd);
	while(line && !check_that(*data))
	{
		if(line[0])
		{
			fillkey_value(line, &key, &value);
			if (!key)
				return (wrerror("invalid8 keyword\n"), -1);
			if (!value)
				return (wrerror("invalid8 value\n"), free(key), -1);
			if (fill_forkey(data, key, value, mlx) == -1)
				return (wrerror("Error777\n"), free(key), free(value),-1);
			free(key);
			free(value);
		}
		line = get_next_line(fd);
		(*data)->lc_tillstartofmap++;
	}
}

int fn_open(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if(fd == -1)
		wrerror("Error :2 opening file\n");
	return (fd);
}

int parsing(t_data **data, t_strct **mlx, char *filename)
{
	int fd;
	char *line;

	fd = fn_open(filename);
	if (fd == -1)
		return (-1);
	if (parse_clrs_txtrs(data, mlx, fd) == -1)
		return (-1);
	if (check_that(*data) == 0 || (line = get_next_line(fd)) == NULL)
		return (wrerror("Error5\n"),-1);
	
}
