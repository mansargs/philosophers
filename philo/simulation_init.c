/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:30:47 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/07 13:47:07 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	allocation_forks(t_info *data)
{
	int	i;

	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philos_num);
	if (!data->forks)
		return (printf(RED"Problem with the allocation memory\n"RESET), false);
	if (pthread_mutex_init(&data->stop_mutex, NULL))
		return (printf(RED"Error initializing mutex stop\n"RESET), false);
	if (pthread_mutex_init(&data->print_mutex, NULL))
	{
		pthread_mutex_destroy(&data->stop_mutex);
		return (printf(RED"Error initializing mutex print\n"RESET), false);
	}
	i = -1;
	while (++i < data->philos_num)
	{
		if (pthread_mutex_init(data->forks + i, NULL))
		{
			deallocation_forks(data, i);
			return (printf(RED"Error initializing fork %d\n"RESET, i + 1), false);
		}
	}
	return (true);
}

static bool convert_argc(const int argc, const char **argv, t_info *data)
{
	if (argc == 5)
		data->must_eat = -1;
	else
		data->must_eat = ft_atol(argv[5]);
	if (data->must_eat != -1  && (data->must_eat <= 0 || data->must_eat > INT_MAX))
		return (false);
	data->philos_num = ft_atol(argv[1]);
	if (data->philos_num <= 0 || data->philos_num > INT_MAX)
		return (false);
	data->time_die = ft_atol(argv[2]);
	if (data->time_die <= 0 || data->time_die > INT_MAX)
		return (false);
	data->time_eat = ft_atol(argv[3]);
	if (data->time_eat <= 0 || data->time_eat > INT_MAX)
		return (false);
	data->time_sleep = ft_atol(argv[4]);
	if (data->time_sleep <= 0 || data->time_sleep > INT_MAX)
		return (false);
	return (true);
}

bool	init_simulation_info(const int argc, const char **argv, t_info *data)
{
	if (!convert_argc(argc, argv, data))
		return (printf(RED"Invalid arguments: must be numbers in (0, INT_MAX]\n"RESET), false);
	if (!allocation_forks(data))
		return (false);
	if (!allocation_philos_monitor(data))
	{
		deallocation_forks(data, data->philos_num);
		return (false);
	}
	return (true);
}



