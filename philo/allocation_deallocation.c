/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation_deallocation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:30:47 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/03 16:00:17 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	deallocation_mutexes(pthread_mutex_t *forks, unsigned int init_count)
{
	int	j;

	j = -1;
	while (++j < init_count)
		pthread_mutex_destroy(forks + j);
	free(forks);
}

bool	allocation_philos_monitor(t_info *data)
{
	int	i;
	int	s;

	data->threads = malloc(sizeof(t_philo) * (data->philos_num + 1));
	if (!data->threads)
	{
		printf("\033[31mProblem with the allocation memory\033[0m\n");
		return (false);
	}
	i = -1;
	while (++i < data->philos_num)
	{
		data->threads[i].counter = 0;
		data->threads[i].index = i + 1;
		data->threads[i].right = data->forks + i;
		data->threads[i].simulation_start = get_time_ms();
		if (i + 1 == data->philos_num)
			data->threads[i].left = data->forks;
		else
			data->threads[i].left = data->forks + i + 1;
		data->threads[i].data = data;
		if (data->philos_num == 1)
			break ;
		if (pthread_create(&data->threads[i].tid, NULL, thread_handler, &data->threads[i]))
		{
			printf("\033[31mError creating thread %d\033[0m\n", i + 1);
			return (false);
		}
	}
	if (data->philos_num == 1)
	{
		if (pthread_create(&data->threads[i].tid, NULL, one_philo, &data->threads[i]))
		{
			printf("\033[31mError creating thread %d\033[0m\n", i + 1);
			return (false);
		}
	}
	else if (pthread_create(&data->threads[i].tid, NULL, monitor_handler, data))
	{
		printf("\033[31mError creating thread %d\033[0m\n", i + 1);
		return (false);
	}
	return (true);
}

bool	allocation_mutexes(t_info *data)
{
	int	i;

	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philos_num);
	if (!data->forks)
	{
		printf("\033[31mProblem with the allocation memory\033[0m\n");
		return (false);
	}
	if (pthread_mutex_init(&data->save_stoping, NULL))
	{
		printf("\033[31mError initializing thread %d\033[0m\n", i + 1);
		return (false);
	}
	i = -1;
	while (++i < data->philos_num)
	{
		if (pthread_mutex_init(data->forks + i, NULL) != 0)
		{
			deallocation_mutexes(data->forks, i);
			pthread_mutex_destroy(&data->save_stoping);
			printf("\033[31mError initializing thread %d\033[0m\n", i + 1);
			return (false);
		}
	}
	return (true);
}

bool	init_simulation_info(const int argc, char **argv, t_info *data)
{
	if (argc == 5)
		data->eat_limit = -1;
	else
		data->eat_limit = ft_atoi(argv[5]);
	data->philos_num = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->stop = false;
	if (!allocation_mutexes(data))
		return (false);
	if (!allocation_philos_monitor(data))
		return (false);
	return (true);
}



