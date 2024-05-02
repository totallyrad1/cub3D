/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:47:07 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/02 18:29:28 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

int	gun_sound(char *s)
{
	int		pid;
	char	*ss;

	if (access(s, R_OK) || access("/usr/bin/afplay", X_OK))
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	ss = ft_strjoin(ft_strdup("/usr/bin/afplay "), s);
	if (!pid)
	{
		system(ss);
		exit(0);
	}
	free(ss);
	return (0);
}
