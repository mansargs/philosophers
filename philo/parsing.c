/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:29:05 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/11 02:21:46 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	changed_atol(const char *str)
{
	size_t		i;
	long int	num;

	if (!str)
		return (-1);
	i = 0;
	num = 0;
	while ((str[i] && str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		++i;
	if (str[i] && str[i] == '-')
		return (-1);
	else if (str[i] && str[i] == '+')
		++i;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = 10 * num + (str[i++] - 48);
		if (num > INT_MAX)
			return (-1);
	}
	if (str[i])
		return (-1);
	return (num);
}

bool convert_argc(const char **argv, t_info *data)
{
	data->philos_number = changed_atol(argv[1]);
	data->time_die = changed_atol(argv[2]);
	data->time_eat = changed_atol(argv[3]);
	data->time_sleep = changed_atol(argv[4]);
	data->must_eat = changed_atol(argv[5]);
	if (data->philos_number < 0 || data->philos_number > 200 || data->time_die < 60 ||
		data->time_eat < 60 || data->time_sleep < 60)
		return (false);
	return (true);
}
