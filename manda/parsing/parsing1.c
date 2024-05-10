/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:47:49 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/10 14:19:45 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_that(t_data *data)
{
	if (data->so != NULL && data->ea != NULL
		&& data->we != NULL && data->no != NULL
		&& data->f_color != -1 && data->c_color != -1)
		return (1);
	return (0);
}

void	fillkey_value(char *line, char **key, char **value)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	*key = NULL;
	*value = NULL;
	while (line[i] && ft_isspace(line[i]))
		i++;
	tmp = i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	*key = ft_substr(line, tmp, i - tmp);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i])
		*value = ft_substr(line, i, ft_strlen(line));
	else
		*value = NULL;
	if (line)
		free(line);
}

int	check_kv(char *key, char *value)
{
	if (!key)
		return (wrerror("invalid8 keyword\n"), -1);
	if (!value)
		return (wrerror("invalid8 value\n"), free(key), -1);
	return (1);
}

int	parse_clrs_txtrs(t_data **data, t_strct **mlx, int fd)
{
	char	*line;
	char	*key;
	char	*value;

	line = get_next_line(fd);
	while (line && !check_that(*data))
	{
		if (line && line[0])
		{
			fillkey_value(line, &key, &value);
			if (check_kv(key, value) == -1)
				return (-1);
			if (fill_forkey(data, key, value, mlx) == -1)
				return (wrerror("Error777\n"), free(key), free(value), -1);
			free(key);
			free(value);
		}
		else
			free(line);
		(*data)->lc_tillstartofmap++;
		if (check_that(*data) == 1)
			return (1);
		line = get_next_line(fd);
	}
	return (1);
}
