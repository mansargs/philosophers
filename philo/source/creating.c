/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:47:09 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/28 19:30:43 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_philosophers(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_number)
	{
		data->philos[i].last_eat = data->start_time;
		data->philos[i].counter = 0;
		data->philos[i].number = i + 1;
		data->philos[i].data = data;
		data->philos[i].left = data->forks + i;
		data->philos[i].right = data->forks + ((i + 1) % data->philos_number);
	}
	return (true);
}

static bool	create_monitor_threads(t_info *data)
{
	if (!data->monitors)
		return (true);
	if (pthread_create(&data->monitors[0], NULL, check_died, data))
		return (printf("\033[0;31mError creating death monitor thread\n\
			\033[0m"), false);
	if (data->must_eat > 0)
	{
		if (pthread_create(&data->monitors[1], NULL, check_full, data))
			return (printf("\033[0;31mError creating full monitor thread\n\
				\033[0m"), false);
	}
	return (true);
}

static void	print_error_and_activate_flag(t_info *data, int index)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("\033[0;31mError creating philosopher thread %d\n\033[0m", index);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = true;
	pthread_mutex_unlock(&data->stop_mutex);
	pthread_detach(data->monitors[0]);
	if (data->must_eat > 0)
		pthread_detach(data->monitors[1]);
	while (--index >= 0)
		pthread_join(data->philos[index].tid, NULL);
}

bool	create_threads(t_info *data)
{
	int	i;

	data->start_time = get_time_ms();
	if (!init_philosophers(data))
		return (false);
	if (!create_monitor_threads(data))
		return (false);
	if (data->philos_number == 1)
	{
		if (pthread_create(&data->philos[0].tid, NULL,
				one_philo, &data->philos[0]))
			return (printf("\033[0;31mError creating philosopher thread\n\
				\033[0m"), false);
		return (true);
	}
	i = -1;
	while (++i < data->philos_number)
	{
		if (pthread_create(&data->philos[i].tid, NULL,
				thread_handler, &data->philos[i]))
			break ;
	}
	if (i < data->philos_number)
		return (print_error_and_activate_flag(data, i), false);
	return (true);
}
