/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:48:54 by asnaji            #+#    #+#             */
/*   Updated: 2024/03/18 21:26:49 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char **newmapfn(void)
{
	int arraysize = 0;
	int longestline = 0;
	int i = 0;
	int fd = open("map.cub", O_CREAT | O_RDWR, 0777);
	char **newmap;
	char *line;
	line = NULL;
	line = get_next_line(fd);
	if(!line)
		return NULL;
	while(line)
	{
		arraysize++;
		if((int)ft_strlen(line) > longestline)
			longestline = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	if	(line)
		free(line);
	close(fd);
	newmap = malloc(sizeof(char *) * (arraysize + 1));
	if (!newmap)
		return (NULL);
	newmap[arraysize] = NULL;
	fd = open("map.cub", O_CREAT | O_RDWR, 0777);
	line = NULL;
	line = get_next_line(fd);
	if(!line)
		return NULL;
	while(newmap[i] && line)
	{
		newmap[i] = linemodified(line, longestline);
		line = get_next_line(fd);
		i++;
	}
	newmap[i] = NULL;
	return newmap;
}
