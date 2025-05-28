/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:20:26 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/28 16:31:04 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_handler(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	printf("working thread %lu\n", philo->tid);
	return (NULL);
}

static bool	complete_info(const int argc, const char **argv, t_info *data)
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
		if (pthread_create(&data->philos[i].tid, NULL, thread_handler, &data->philos[i]) != 0)
		{
			printf("\033[31mError creating thread %d\033[0m\n", i + 1);
			return (false);
		}
		++i;
	}
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
			j = 0;
			while (++i )
		}


	}

	return (true);
}

int	main(int argc, char **argv)
{
	t_info			data;
	unsigned int	i;

	if (argc < 5 || argc > 6 || !valid_arguments(argc, argv))
	{
		printf(INVALID_ARGC);
		return (EINVAL);
	}
	if (!complete_info(argc, (const char **)argv, &data))
		return (ENOMEM);

	i = 0;
	while (i < data.philos_num)
	{
		pthread_join(data.philos[i].tid, NULL);
		++i;
	}

	free(data.philos);
	return (EXIT_SUCCESS);
}
