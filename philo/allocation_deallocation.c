/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation_deallocation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:30:47 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/03 01:36:41 by mansargs         ###   ########.fr       */
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

bool	allocation_philos(t_info *data)
{
	int	i;
	int	s;

	data->philos = malloc(sizeof(t_philo) * (data->philos_num + 2));
	if (!data->philos)
	{
		printf("\033[31mProblem with the allocation memory\033[0m\n");
		return (false);
	}
	i = -1;
	while (++i < data->philos_num)
	{
		data->philos[i].index = i + 1;
		data->philos[i].right = data->forks + i;
		if (i + 1 == data->philos_num)
			data->philos[i].left = data->forks;
		else
			data->philos[i].left = data->forks + i + 1;
		data->philos[i].data = data;
		if (data->philos_num == 1)
			break ;
		if (pthread_create(&data->philos[i].tid, NULL, thread_handler, &data->philos[i]))
		{
			printf("\033[31mError creating thread %d\033[0m\n", i + 1);
			return (false);
		}
	}
	if (data->philos_num == 1)
	{
		if (pthread_create(&data->philos[i].tid, NULL, one_philo, &data->philos[i]))
		{
			printf("\033[31mError creating thread %d\033[0m\n", i + 1);
			return (false);
		}
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
	i = -1;
	while (++i < data->philos_num)
	{
		if (pthread_mutex_init(data->forks + i, NULL) != 0)
		{
			deallocation_mutexes(data->forks, i);
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
	if (!allocation_mutexes(data))
		return (false);
	if (!allocation_philos(data))
		return (false);
	data->simulation_start = get_time_ms();
	return (true);
}



