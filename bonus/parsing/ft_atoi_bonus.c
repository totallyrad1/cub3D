/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:47:32 by mozennou          #+#    #+#             */
/*   Updated: 2024/04/02 15:47:33 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus.h"

int ft_atoi(char *str, int *j)
{
	int res;

	res = 0;
	while (str[*j] && (str[*j] >= '0' && str[*j] <= '9'))
	{
		res = res * 10 + (str[*j] - '0');
		(*j)++;
	}
	if (str[*j] == ',')
		(*j)++;
	while(str[*j] && ft_isspace(str[*j]))
			(*j)++;
	return (res);
}