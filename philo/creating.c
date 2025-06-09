/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:47:09 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/09 15:15:56 by mansargs         ###   ########.fr       */
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

void	philo

static bool create_philos(t_info *data)
{
	int	i;

	i = -1;
	timestamp_ms(data->start_time);
	if (data->philos_number == 1)
	{
		++i;

		if (pthread_create(&data->philos[i].tid, NULL, one_philo, &data->philos[i]))
			return (printf(RED"Error creating thread %d\n"RESET, i + 1), false);
	}
	while (++i < data->philos_number)
	{

		if (pthread_create(&data->philos[i].tid, NULL, thread_handler, &data->philos[i]))
			return (printf(RED"Error creating thread %d\n"RESET), false);
	}

	return (true);
}

