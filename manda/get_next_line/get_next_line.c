/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:56:34 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/02 15:49:13 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(char *buffer, int fd, char *hold)
{
	int	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && newlineexists(hold) == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(hold);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		hold = ft_strjoin(hold, buffer);
	}
	free(buffer);
	if (hold)
	{
		if (hold[0] == '\0')
			return (free(hold), NULL);
	}
	return (hold);
}

char	*ft_getline(char *hold)
{
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	if (!hold)
		return (NULL);
	while (hold[i] && hold[i] != '\n')
		i++;
	res = ft_substr(hold, 0, i);
	return (res);
}

char	*ft_remreturnedline(char *hold)
{
	char	*res;
	int		i;

	i = 0;
	if (!hold)
		return (free(hold), NULL);
	while (hold[i] && hold[i] != '\n')
		i++;
	if (hold[i] == '\n')
		i++;
	res = ft_strdup(&hold[i]);
	free(hold);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*hold = NULL;
	char		*line;
	char		*buffer;

	if ((fd < 0 && fd < OPEN_MAX) || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	hold = ft_read(buffer, fd, hold);
	line = ft_getline(hold);
	hold = ft_remreturnedline(hold);
	return (line);
}
