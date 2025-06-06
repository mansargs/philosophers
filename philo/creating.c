/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:47:09 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/06 14:47:04 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void destroy_internal_mutexes(t_info *data, int up_to)
{
	int	i;

	i= -1;
	while (++i < up_to)
	{
		pthread_mutex_destroy(&data->philos[i].counter_mutex);
		pthread_mutex_destroy(&data->philos[i].last_eat_mutex);
	}
}

static void	private_philo(t_info	*data, int index)
{
	data->philos[index].last_eat = get_time_ms();
	data->philos[index].counter = 0;
	data->philos[index].index = index + 1;
	data->philos[index].right = data->forks + index;
	data->philos[index].left = data->forks + ((index + 1) % data->philos_num);
	data->philos[index].data = data;
}

static bool create_monitor_threads(t_info *data)
{
	data->monitors = (pthread_t	*)malloc(sizeof(pthread_t) * 2);
	if (!data->monitors)
		return (printf(RED"Problem with the allocation memory\n"RESET), false);
	if (pthread_create(data->monitors, NULL, check_died, data))
		return (printf(RED"Error creating monitor thread %d\n"RESET), false);
	if (pthread_create(data->monitors + 1, NULL, check_full, data))
		return (printf(RED"Error creating monitor thread %d\n"RESET), false);
	return (true);
}

static bool create_philos(t_info *data)
{
	int	i;

	i = -1;
	data->start_time = get_time_ms();
	if (data->philos_num == 1)
	{
		++i;
		private_philo(data, i);
		if (pthread_create(&data->philos[i].tid, NULL, one_philo, &data->philos[i]))
			return (printf(RED"Error creating thread %d\n"RESET, i + 1), false);
	}
	while (++i < data->philos_num)
	{
		private_philo(data, i);
		if (pthread_create(&data->philos[i].tid, NULL, thread_handler, &data->philos[i]))
			return (printf(RED"Error creating thread %d\n"RESET, i + 1), false);
	}

	return (true);
}

static bool init_internal_mutexes(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_num)
	{
		if (pthread_mutex_init(&data->philos[i].counter_mutex, NULL))
		{
			destroy_internal_mutexes(data, i);
			return (false);
		}
		if (pthread_mutex_init(&data->philos[i].last_eat_mutex, NULL))
		{
			pthread_mutex_destroy(&data->philos[i].counter_mutex);
			destroy_internal_mutexes(data, i);
			return (false);
		}
	}
	return (true);
}

bool allocation_philos_monitor(t_info *data)
{
	data->philos = (t_philo *)malloc(sizeof(t_philo) * (data->philos_num));
	if (!data->philos)
		return (printf(RED"Problem with the allocation memory\n"RESET), false);
	if (!init_internal_mutexes(data))
		return (printf(RED"Problem initializing mutexes\n"RESET), false);
	if (!create_threads(data))
		return (destroy_internal_mutexes(data, data->philos_num), false);
	if (data->philos_num != 1)
		if (!create_monitor_threads(data))
			return (destroy_internal_mutexes(data, data->philos_num), false);
	return (true);
}
