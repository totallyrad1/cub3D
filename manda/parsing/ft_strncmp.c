/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:47:36 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/10 14:19:39 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	fn_open(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		wrerror("Error :2 opening file\n");
	return (fd);
}

int	parsing(t_data *data, t_strct *mlx, char *filename)
{
	int	fd;

	fd = fn_open(filename);
	if (fd == -1)
		return (-1);
	if (parse_clrs_txtrs(&data, &mlx, fd) == -1)
		return (close(fd), -1);
	if (check_that(data) == 0)
		return (close(fd), wrerror("Error5\n"), -1);
	if (get_map(&data, filename, fd) == -1)
		return (close(fd), wrerror("Error7\n"), -1);
	return (1);
}
