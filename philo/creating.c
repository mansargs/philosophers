/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:47:09 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/11 13:34:54 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool init_philosophers(t_info *data)
{
	int i;

	i = -1;
	while (++i < data->philos_number)
	{
		data->philos[i].last_eat = data->start_time;
		data->philos[i].counter = 0;
	}
	return (true);
}

static bool create_monitor_threads(t_info *data)
{
	if (pthread_create(&data->monitors[0], NULL, check_died, data))
		return (printf(RED"Error creating death monitor thread\n"RESET), false);

	if (data->must_eat > 0)
	{
		if (pthread_create(&data->monitors[1], NULL, check_full, data))
			return (printf(RED"Error creating full monitor thread\n"RESET), false);
	}
	return (true);
}

bool create_threads(t_info *data)
{
	int i;

	data->stop = false;
	data->start_time = get_time_ms();

	if (!init_philosophers(data))
		return (false);

	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (printf(RED"Error initializing print mutex\n"RESET), false);
	if (pthread_mutex_init(&data->stop_mutex, NULL))
		return (printf(RED"Error initializing stop mutex\n"RESET), false);

	if (data->philos_number == 1)
	{
		if (pthread_create(&data->philos[0].tid, NULL, one_philo, &data->philos[0]))
			return (printf(RED"Error creating single philosopher thread\n"RESET), false);
		return (true);
	}
	i = -1;
	while (++i < data->philos_number)
	{
		if (pthread_create(&data->philos[i].tid, NULL, thread_handler, &data->philos[i]))
			return (printf(RED"Error creating philosopher thread %d\n"RESET, i), false);
	}

	// Small delay to ensure philosophers are ready before monitors start
	usleep(1000);

	if (!create_monitor_threads(data))
		return (false);

	return (true);
}
