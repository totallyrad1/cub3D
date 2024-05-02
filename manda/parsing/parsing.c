#include "../header.h"

char	*linemodified(char *line, int longestline)
{
	char	*newline;
	int		i;

	newline = malloc(longestline + 1);
	if (!newline)
		return (NULL);
	i = 0;
	while (i < longestline && line[i])
	{
		newline[i] = line[i];
		i++;
	}
	while (i < longestline)
		newline[i++] = ' ';
	newline[i] = '\0';
	free(line);
	return (newline);
}

void	free_array(char **line)
{
	int	i;

	i = 0;
	if (line)
	{
		while (line[i])
			free(line[i++]);
		free(line);
	}
}

int	checkandreturn(int w, int h, void *img)
{
	if (img == NULL || w != 512 || h != 512)
		return (-1);
	return (0);
}

int	settextures_value(char *key, t_data **data, t_strct **mlx, char *value)
{
	int	w;
	int	h;

	if (!ft_strcmp(key, "SO") && !(*data)->so)
	{
		(*data)->so = mlx_xpm_file_to_image((*mlx)->mlx, value, &w, &h);
		return (checkandreturn(w, h, (*data)->so));
	}
	else if (!ft_strcmp(key, "EA") && !(*data)->ea)
	{
		(*data)->ea = mlx_xpm_file_to_image((*mlx)->mlx, value, &w, &h);
		return (checkandreturn(w, h, (*data)->ea));
	}
	else if (!ft_strcmp(key, "NO") && !(*data)->no)
	{
		(*data)->no = mlx_xpm_file_to_image((*mlx)->mlx, value, &w, &h);
		return (checkandreturn(w, h, (*data)->no));
	}
	else if (!ft_strcmp(key, "WE") && !(*data)->we)
	{
		(*data)->we = mlx_xpm_file_to_image((*mlx)->mlx, value, &w, &h);
		return (checkandreturn(w, h, (*data)->we));
	}
	else
		return (-1);
}
