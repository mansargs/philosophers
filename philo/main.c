/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:20:26 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/03 16:14:30 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	 return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

void	*thread_handler(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (!philo->data->stop)
	{
		if (philo->index % 2 == 1)
		{
			pthread_mutex_lock(philo->right);
			printf(TAKE_FORK, get_time_ms(), philo->index);
			pthread_mutex_lock(philo->left);
			printf(TAKE_FORK, get_time_ms(), philo->index);
		}
		else
		{
			pthread_mutex_lock(philo->left);
			printf(TAKE_FORK, get_time_ms(), philo->index);
			pthread_mutex_lock(philo->right);
			printf(TAKE_FORK, get_time_ms(), philo->index);
		}
		printf(EATING, get_time_ms(), philo->index);
		++philo->counter;
		usleep(philo->data->time_eat);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		printf(SLEEPING, get_time_ms(), philo->index);
		usleep(philo->data->time_sleep);
		printf(THINKING, get_time_ms(), philo->index);
	}
	return (NULL);
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	printf(TAKE_FORK, get_time_ms(), philo->index);
	usleep(philo->data->time_die + 10);
	printf(DIED, get_time_ms(), philo->index);
	return (NULL);
}


void	*monitor_handler(void	*arg)
{
	t_info	*data;
	int		i;
	bool	all;

	data = (t_info *) arg;
	if (data->eat_limit != -1)
	{
		i = -1;
		while (++i < data->philos_num)
		{
			printf("%d counter is %d",data->threads[i].index, data->threads[i].counter);
			if (data->threads[i].counter != data->eat_limit)
			{
				all = false;
				break ;
			}
			all = true;
		}
		if (all)
		{
			printf(SUCCESS_FINISH);
			data->stop = true;
			return (NULL);
		}
	}
	i = -1;
	while (++i < data->philos_num)
	{
		if (get_time_ms() - data->threads[i].simulation_start >= data->time_die)
		{
			printf(DIED, get_time_ms(), data->threads[i].index);
			data->stop = true;
			return (NULL);
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_info	data;
	int		i;

	if (argc < 5 || argc > 6 || !valid_arguments(argc, argv))
	{
		printf(INVALID_ARGC);
		return (EINVAL);
	}
	if (!init_simulation_info(argc, argv, &data))
		return (EXIT_FAILURE);
	i = -1;
	int total_threads = data.philos_num + (data.philos_num > 1);
	while (i < total_threads)
		pthread_join(data.threads[i].tid, NULL);
	free(data.threads);
	return (EXIT_SUCCESS);
}
