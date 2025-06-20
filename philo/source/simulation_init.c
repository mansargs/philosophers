/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:30:47 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/13 15:13:05 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_internal_mutexes(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_number)
	{
		if (pthread_mutex_init(&data->philos[i].counter_mutex, NULL))
		{
			destroy_internal_mutexes(data, i);
			return (printf("\033[0;31mError initializing mutex\n\033[0m"),
				false);
		}
		if (pthread_mutex_init(&data->philos[i].last_eat_mutex, NULL))
		{
			pthread_mutex_destroy(&data->philos[i].counter_mutex);
			destroy_internal_mutexes(data, i);
			return (printf("\033[0;31mError initializing mutex\n\033[0m"),
				false);
		}
	}
	return (true);
}

static bool	initialize_mutexes(t_info *data)
{
	int	i;

	if (pthread_mutex_init(&data->stop_mutex, NULL))
		return (printf("\033[0;31mError init mutex\n\033[0m"), false);
	if (pthread_mutex_init(&data->print_mutex, NULL))
	{
		pthread_mutex_destroy(&data->stop_mutex);
		return (printf("\033[0;31mError init mutex\n\033[0m"), false);
	}
	i = -1;
	while (++i < data->philos_number)
	{
		if (pthread_mutex_init(data->forks + i, NULL))
		{
			deallocation_forks(data, i);
			return (printf("\033[0;31mError initializing fork\n\033[0m"),
				false);
		}
	}
	if (!init_internal_mutexes(data))
		return (pthread_mutex_destroy(&data->stop_mutex),
			pthread_mutex_destroy(&data->print_mutex),
			deallocation_forks(data, i), false);
	return (true);
}

static bool	allocation(t_info *data)
{
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philos_number);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philos_number);
	if (data->philos_number != 1)
		data->monitors = (pthread_t *)malloc(sizeof(pthread_t)
				* (1 + (data->must_eat != -1)));
	if (!data->forks || (!data->monitors && data->philos_number != 1)
		|| !data->philos)
		return (printf("\033[0;31Problem with the allocation memory\n\033[0m"),
			false);
	if (!initialize_mutexes(data))
		return (false);
	return (true);
}

bool	init_simulation_info(const char **argv, t_info *data)
{
	if (!convert_argc(argv, data))
		return (printf("\033[0;31mInvalid arguments\n\033[0m"), false);
	if (!allocation(data))
		return (false);
	return (true);
}
