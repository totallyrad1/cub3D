/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_write_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:47:19 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/08 14:57:24 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus.h"

void	wrerror(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
}

int	checkvalues(int i1, int i2, int i3)
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
