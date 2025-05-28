/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation_deallocation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:30:47 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/28 17:57:41 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	deallocation_mutexes(pthread_mutex_t *forks, unsigned int index)
{
	unsigned int	j;

	j = 0;
	while (j < index)
	{
		pthread_mutex_destroy(forks + j);
		++j;
	}
	free(forks);
}

bool	allocation_philos(t_info *data)
{
	unsigned int	i;

	data->philos = malloc(sizeof(t_philo) * data->philos_num);
	if (!data->philos)
	{
		printf("\033[31mProblem with the allocation memory\033[0m\n");
		return (false);
	}
	i = 0;
	while (i < data->philos_num)
	{
		data->philos[i].index = i + 1;
		if (pthread_create(&data->philos[i].tid, NULL, thread_handler, &data->philos[i]))
		{
			printf("\033[31mError creating thread %d\033[0m\n", i + 1);
			return (false);
		}
		++i;
	}
	return (true);
}

bool	allocation_mutexes(t_info *data)
{
	unsigned int i;

	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philos_num);
	if (!data->forks)
	{
		printf("\033[31mProblem with the allocation memory\033[0m\n");
		return (false);
	}
	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_mutex_init(data->forks + i, NULL) != 0)
		{
			destroy_mutexes(data->forks, i);
			printf("\033[31mError initializing thread %d\033[0m\n", i + 1);
			return (false);
		}
		++i;
	}
	return (true);
}

bool	init_simulation_info(const int argc, const char **argv, t_info *data)
{
	unsigned int	i;
	unsigned int	j;

	if (argc == 5)
		data->eat_limit = -1;
	else
		data->eat_limit = ft_atoi(argv[5]);
	data->philos_num = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (!allocation_philos(data))
		return (false);
	if (!allocation_mutexes(data))
	{
		free(data->philos);
		return (false);
	}
	return (true);
}



