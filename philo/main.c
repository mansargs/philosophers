/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:20:26 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/04 02:24:18 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	 return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

void safe_print(t_info *data, const char *str, const int index)
{
	pthread_mutex_lock(&data->save_stoping);

	if (!data->stop)
	{
		// Hold the stop mutex while printing to prevent race conditions.
		pthread_mutex_lock(&data->save_printing);
		printf(str, get_time_ms(), index);
		pthread_mutex_unlock(&data->save_printing);
	}

	pthread_mutex_unlock(&data->save_stoping);
}

void	*thread_handler(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;

	while (1)
	{
		pthread_mutex_lock(&philo->data->save_stoping);
		while (!philo->data->stop)
		{
			pthread_mutex_unlock(&philo->data->save_stoping);
			if (philo->index % 2 == 1)
			{
				pthread_mutex_lock(philo->right);
				safe_print(philo->data, TAKE_FORK, philo->index);
				pthread_mutex_lock(philo->left);
				safe_print(philo->data, TAKE_FORK, philo->index);
			}
			else
			{
				pthread_mutex_lock(philo->left);
				safe_print(philo->data, TAKE_FORK, philo->index);
				pthread_mutex_lock(philo->right);
				safe_print(philo->data, TAKE_FORK, philo->index);
			}
			safe_print(philo->data, EATING, philo->index);
			++philo->counter;
			usleep(philo->data->time_eat);
			philo->last_eat = get_time_ms ();
			pthread_mutex_unlock(philo->left);
			pthread_mutex_unlock(philo->right);
			philo->last_eat += philo->data->time_sleep;
			safe_print(philo->data, SLEEPING, philo->index);
			usleep(philo->data->time_sleep);
			safe_print(philo->data, THINKING, philo->index);
		}
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
	while (!data->stop)
	{
		if (data->eat_limit != -1)
		{
			i = -1;
			all = true;
			while (++i < data->philos_num)
			{
				if (data->threads[i].counter != data->eat_limit)
				{
					all = false;
					break ;
				}
			}
			if (all)
			{
				printf(SUCCESS_FINISH);
				pthread_mutex_lock(&data->save_stoping);
				data->stop = true;
				pthread_mutex_unlock(&data->save_stoping);
				return (NULL);
			}
		}
		i = -1;
		while (++i < data->philos_num)
		{
			if (get_time_ms() - data->threads[i].last_eat >= data->time_die)
			{
				printf(DIED, get_time_ms(), data->threads[i].index);
				pthread_mutex_lock(&data->save_stoping);
				data->stop = true;
				pthread_mutex_unlock(&data->save_stoping);
				return (NULL);
			}
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
	while (++i <= data.philos_num)
		pthread_join(data.threads[i].tid, NULL);
	free(data.threads);
	return (EXIT_SUCCESS);
}
