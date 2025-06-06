/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:30:47 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/06 03:07:16 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	private_philo(t_info	*data, int index)
{
	data->threads[index].counter = 0;
	data->threads[index].last_eat = data->start_time;
	data->threads[index].index = index + 1;
	data->threads[index].right = data->forks + index;
	data->threads[index].left = data->forks + ((index + 1) % data->philos_num);
	data->threads[index].last_eat = get_time_ms();
	data->threads[index].data = data;
}

static allocation_internal_mutexes(t_info	*data)
{
	int	i;

	i = -1;
	while (++i < data->philos_num)
	{
		if ()
	}
}

bool	allocation_philos_monitor(t_info *data)
{
	int	i;

	if (data->philos_num != 1)
		data->threads = malloc(sizeof(t_philo) * (data->philos_num + 2));
	else
		data->threads = malloc(sizeof(t_philo) * (data->philos_num));
	if (!data->threads)
		return (printf(RED"Problem with the allocation memory\n"RESET), false);
	i = -1;
	data->start_time = get_time_ms ();
	if (!allocation_internal_mutexes(data))
	while (++i < data->philos_num)
	{
		private_philo(data, i);
		if (data->philos_num == 1)
			break ;
		if (pthread_create(&data->threads[i].tid, NULL, thread_handler, &data->threads[i]))
			return (printf(RED"Error creating thread %d\n"RESET, i + 1), false);
	}
	if (data->philos_num == 1)
	{
		if (pthread_create(&data->threads[i].tid, NULL, one_philo, &data->threads[i]))
			return (printf(RED"Error creating thread %d\n"RESET, i + 1), false);
		++i;
	}
	if (pthread_create(&data->threads[i].tid, NULL, monitor_handler, data))
		return (printf(RED"Error creating monitor thread\n"RESET), free(data->threads), false);
	return (true);
}

bool	allocation_mutexes(t_info *data)
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
			deallocation_mutexes(data, i);
			return (printf(RED"Error initializing mutex %d\n"RESET, i + 1), false);
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
		return (printf(RED"The number must be in (0, INT_MAX] range\n"RESET), false);
	if (!allocation_mutexes(data))
		return (false);
	if (!allocation_philos_monitor(data))
	{
		deallocation_mutexes(data, data->philos_num);
		return (false);
	}
	allocation_internal_mutexes()
	return (true);
}



