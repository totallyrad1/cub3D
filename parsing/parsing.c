#include "../header.h"

char *linemodified(char *line, int longestline)
{
	char *newline = malloc(longestline + 1);
	int i = 0;
	while(i < longestline && line[i])
	{
		newline[i] = line[i];
		i++;
	}
	while(i < longestline)
		newline[i++] = ' ';
	newline[i] = '\0';
	free(line);
	return (newline);
}

void free_array(char **line)
{
	int	i;

	i = 0;
	if (line)
	{
		while(line[i])
			free(line[i++]);
		free(line);
	}
}

int validkeyword(char *keyword)
{
	if(!keyword)
		return (0);
	if (!ft_strcmp(keyword, "SO"))
		return (1);
	if (!ft_strcmp(keyword, "EA"))
		return (1);
	if (!ft_strcmp(keyword, "NO"))
		return (1);
	if (!ft_strcmp(keyword, "WE"))
		return (1);
	return (0);
}

int validkeyword1(char *keyword)
{
	if(!keyword)
		return (0);
	if (!ft_strcmp(keyword, "C"))
		return (1);
	if (!ft_strcmp(keyword, "F"))
		return (1);
	return (0);
}

void setvalue(char **linesplit, t_data **data, t_strct **mlx)
{
	int w;
	int h;
	if (!ft_strcmp(linesplit[0], "SO"))
		(*data)->so = mlx_xpm_file_to_image((*mlx)->mlx, linesplit[1], &w, &h);
	else if (!ft_strcmp(linesplit[0], "EA"))
		(*data)->ea = mlx_xpm_file_to_image((*mlx)->mlx, linesplit[1], &w, &h);
	else if (!ft_strcmp(linesplit[0], "NO"))
		(*data)->no = mlx_xpm_file_to_image((*mlx)->mlx, linesplit[1], &w, &h);
	else if (!ft_strcmp(linesplit[0], "WE"))
		(*data)->we = mlx_xpm_file_to_image((*mlx)->mlx, linesplit[1], &w, &h);
}

int checkvalues(int i1, int i2, int i3)
{
	if (i1 < 0 || i1 > 255)
		return (0);
	if (i2 < 0 || i2 > 255)
		return (0);
	if (i3 < 0 || i3 > 255)
		return (0);
	return (1);
}

int	to_color(int r, int g, int b)
{
	return (((r) << 16) | ((g) << 8) | (b));
}

int setvalue1(char **linesplit, t_data **data)
{
	int j;
	int	r;
	int	g;
	int	b;

	j = 0;
	if (!ft_strcmp(linesplit[0], "C"))
	{
		r = ft_atoi(linesplit[1], &j);
		g = ft_atoi(linesplit[1], &j);
		b = ft_atoi(linesplit[1], &j);
		if(!checkvalues(r, g, b))
			return (0);
		(*data)->f_color = to_color(r, g, b);
	}
	if (!ft_strcmp(linesplit[0], "F"))
	{
		r = ft_atoi(linesplit[1], &j);
		g = ft_atoi(linesplit[1], &j);
		b = ft_atoi(linesplit[1], &j);
		if(!checkvalues(r, g, b))
			return (0);
		(*data)->c_color = to_color(r, g, b);
	}
	return (1);
}

int	fill_walls(t_data **data, t_strct **mlx, int fd)
{
	char	*line;
	char	**linesplit;
	int		i;

	i = 0;
	line = NULL;
	linesplit = NULL;
	while(i < 4)
	{
		line = get_next_line(fd);
		if(!line)
			return (wrerror("invalid line\n"), -1);
		linesplit = ft_split(line, ' ');
		if(!linesplit || !validkeyword(linesplit[0]))
			return (wrerror("invalid keyword\n"), -1);
		setvalue(linesplit, data, mlx);
		free(line);
		free_array(linesplit);
		line = NULL;
		linesplit = NULL;
		i++;
	}
	if (!(*data)->no || !(*data)->so || !(*data)->we || !(*data)->ea)
		return (wrerror("invalid textures\n"), -1);
	return (1);
}

int checkvalidnumbers(char *str)
{
	int ncount;
	int ccount;
	int i;

	i = 0;
	ncount = 0;
	ccount = 0;
	while(str && str[i])
	{
		if(str[i] >= '0' && str[i] <= '9')
			ncount++;
		else
			return(0);
		while(str[i] >= '0' && str[i] <= '9')
			i++;
		if(str[i] && str[i] == ',')
		{
			ccount++;
			i++;
		}
		else if (str[i])
			return(0);
	}
	if (ncount != 3 || ccount != 2)
		return(0);
	return (1);
}

int fillcolors(t_data **data, int fd)
{
	char	*line;
	char	**linesplit;
	int		i;

	i = 0;
	line = NULL;
	linesplit = NULL;
	while (i < 2)
	{
		line = get_next_line(fd);
		if (!line)
			return (wrerror("invalid line\n"), -1);
		linesplit = ft_split(line, ' ');
		if (!linesplit || !validkeyword1(linesplit[0]))
			return (wrerror("invalid keyword\n"), -1);
		if ( !checkvalidnumbers(linesplit[1]))
			return (wrerror("invalid number\n"), -1);
		if (!setvalue1(linesplit, data))
			return (wrerror("invalid numbers\n"), -1);
		free(line);
		free_array(linesplit);
		line = NULL;
		linesplit = NULL;
		i++;
	}
	if((*data)->f_color  == -1 || (*data)->c_color == -1)
		return (wrerror("missing color\n"), -1);
	return (1);
}

int setwallsandcolors(t_data **data, t_strct **mlx, int fd)
{
	char *line;

	if (fill_walls(data, mlx, fd) == -1)
		return (-1);
	line = get_next_line(fd);
	if(!line || line[0] != '\0')
		return(free(line), wrerror("Error\n"), -1);
	free(line);
	if (fillcolors(data, fd) == -1)
		return (-1);
	line = get_next_line(fd);
	if(!line || line[0] != '\0')
		return(free(line), wrerror("Error\n"), -1);
	free(line);
	return (1);
}

int setmap(t_data **data, int fd, char *filename)
{
	int arraysize;
	int longestline;
	char *line;
	int		i;

	arraysize = 0;
	i = 0;
	longestline = 0;
	line = get_next_line(fd);
	while(line)
	{
		arraysize++;
		if((int)ft_strlen(line) > longestline)
			longestline = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	fd = open(filename, O_RDWR);			//not closed file descriptor detected by amine_oz LOL
	if (fd == -1)
	{
		wrerror(filename);
		wrerror(" error opening file\n");
		return (-1);
	}
	(*data)->mp = malloc(sizeof(char *) * (arraysize + 1));
	if (!(*data)->mp)
		return (wrerror("allocation error"), -1);
	(*data)->mp[arraysize] = NULL;
	line = get_next_line(fd);
	while(i < 8)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	i = 0;
	while((*data)->mp[i] && line)
	{
		(*data)->mp[i] = linemodified(line, longestline);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (1);
}

int parse_everything(t_data *data, t_strct *mlx, char *filename)
{
	int		fd;

	fd = open(filename, O_RDWR);
	if (fd == -1)
	{
		wrerror(filename);
		wrerror(" file doesnt exist\n");
		return (-1);
	}
	if (setwallsandcolors(&data, &mlx, fd) == -1)
		return (-1);
	if(setmap(&data, fd, filename) == -1)
		return (-1);
	return (1);
}
