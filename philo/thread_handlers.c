/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:20:26 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/04 16:40:30 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void safe_print(t_info *data, const char *str, const int index)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		return;
	}
	pthread_mutex_lock(&data->print_mutex);
	pthread_mutex_unlock(&data->stop_mutex);

	printf(str, get_time_ms() - data->start_time, index);

	pthread_mutex_unlock(&data->print_mutex);
}

void *thread_handler(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (1)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (philo->data->stop)
		{
			pthread_mutex_unlock(&philo->data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);

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
		philo->last_eat = get_time_ms();

		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);

		safe_print(philo->data, SLEEPING, philo->index);
		usleep(philo->data->time_sleep);

		safe_print(philo->data, THINKING, philo->index);
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
	while (1)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (data->stop)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->stop_mutex);
		if (data->must_eat != -1)
		{
			i = -1;
			all = true;
			while (++i < data->philos_num)
			{
				if (data->threads[i].counter != data->must_eat)
				{
					all = false;
					break ;
				}
			}
			if (all)
			{
				pthread_mutex_lock(&data->print_mutex);
				printf(SUCCESS_FINISH);
				pthread_mutex_unlock(&data->print_mutex);
				pthread_mutex_lock(&data->stop_mutex);
				data->stop = true;
				pthread_mutex_unlock(&data->stop_mutex);
				return (NULL);
			}
		}
		i = -1;
		while (++i < data->philos_num)
		{
			if (get_time_ms() - data->threads[i].last_eat >= data->time_die + data->time_sleep)
			{
				safe_print(data, DIED, data->threads[i].index);
				pthread_mutex_lock(&data->stop_mutex);
				data->stop = true;
				pthread_mutex_unlock(&data->stop_mutex);
				return (NULL);
			}
		}
	}
	return (NULL);
}

