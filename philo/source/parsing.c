/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:29:05 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/15 01:59:33 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_invalid_format(const char *str)
{
	size_t	i;

	i = 0;
	while ((str[i] && str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '0' && str[i + 1])
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	changed_atol(const char *str)
{
	size_t		i;
	long int	num;
	int			sign;

	if (!str || is_invalid_format(str))
		return (-1);
	i = 0;
	num = 0;
	sign = 1;
	while ((str[i] && str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = 10 * num + (str[i++] - '0');
		if (num > INT_MAX)
			return (-1);
	}
	return (sign * num);
}

bool	convert_argc(const char **argv, t_info *data)
{
	data->philos_number = changed_atol(argv[1]);
	data->time_die = changed_atol(argv[2]);
	data->time_eat = changed_atol(argv[3]);
	data->time_sleep = changed_atol(argv[4]);
	data->must_eat = changed_atol(argv[5]);
	if (data->philos_number < 0 || data->philos_number > 12000
		|| data->time_die < 60 || data->time_eat < 60
		|| data->time_sleep < 60 || data->must_eat < -1)
		return (false);
	return (true);
}
