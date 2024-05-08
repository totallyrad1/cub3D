/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:47:32 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/08 14:54:05 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus.h"

int	ft_atoi(char *str, int *j)
{
	int	res;
	int	count;

	res = 0;
	count = 0;
	while (str[*j] && (str[*j] >= '0' && str[*j] <= '9'))
	{
		count++;
		res = res * 10 + (str[*j] - '0');
		(*j)++;
	}
	if (str[*j] == ',')
		(*j)++;
	while (str[*j] && ft_isspace(str[*j]))
		(*j)++;
	if (count > 4)
		return (-1);
	else
		return (res);
}
