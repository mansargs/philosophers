/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:29:05 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/08 22:38:58 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	changed_atol(const char *str)
{
	size_t		i;
	long int	num;

	i = 0;
	num = 0;
	while ((str[i] && str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		++i;
	if (str[i] == '-')
		return (-1);
	else if (str[i] == '+')
		++i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = 10 * num + (str[i++] - 48);
		if (num > INT_MAX)
			return (-1);
	}
	if (str[i])
		return (-1);
	return (num);
}
