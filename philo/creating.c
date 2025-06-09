/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:47:09 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/09 14:05:05 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool create_monitor_threads(t_info *data)
{
	data->monitors = (pthread_t	*)malloc(sizeof(pthread_t) * 2);
	if (!data->monitors)
		return (printf(RED"Problem with the allocation memory\n"RESET), false);
	if (pthread_create(data->monitors, NULL, check_died, data))
		return (printf(RED"Error creating monitor thread\n"RESET), false);
	if (pthread_create(data->monitors + 1, NULL, check_full, data))
		return (printf(RED"Error creating monitor thread\n"RESET), false);
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
	while (++i < data->philos_number)
	{
		private_philo(data, i);
		if (pthread_create(&data->philos[i].tid, NULL, thread_handler, &data->philos[i]))
			return (printf(RED"Error creating thread %d\n"RESET, i + 1), false);
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
	if (!create_philos(data))
		return (destroy_internal_mutexes(data, data->philos_num), false);
	if (data->philos_num != 1)
		if (!create_monitor_threads(data))
			return (destroy_internal_mutexes(data, data->philos_num), false);
	return (true);
}
