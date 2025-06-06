/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:20:26 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/06 15:46:33 by mansargs         ###   ########.fr       */
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
	pthread_mutex_unlock(&data->stop_mutex);
	pthread_mutex_lock(&data->print_mutex);
	printf("[%ld] %d %s\n", get_time_ms() - data->start_time, index, str);
	pthread_mutex_unlock(&data->print_mutex);
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	printf("[%ld] %d %s\n", get_time_ms() - philo->data->start_time, philo->index, TAKE_FORK);
	usleep(philo->data->time_die * 1000);
	printf("[%ld] %d %s\n", get_time_ms() - philo->data->start_time, philo->index, DIED);
	return (NULL);
}

static void	ready_for_eating(t_philo *philo)
{
	if (philo->index % 2)
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
}

static void	eat(t_philo *philo)
{
	safe_print(philo->data, EATING, philo->index);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_time_ms();
	pthread_mutex_unlock(&philo->last_eat_mutex);
	pthread_mutex_lock(&philo->counter_mutex);
	++philo->counter;
	pthread_mutex_unlock(&philo->counter_mutex);
	usleep(philo->data->time_eat * 1000);
}

void	*thread_handler(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (philo->data->stop)
		{
			pthread_mutex_unlock(&philo->data->stop_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
		ready_for_eating(philo);
		eat(philo);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		safe_print(philo->data, SLEEPING, philo->index);
		usleep(philo->data->time_sleep * 1000);
		safe_print(philo->data, THINKING, philo->index);
	}
	return (NULL);
}

void	*check_died(void *arg)
{
	t_info	*data;

	data = (t_info *) arg;

	while (get_time_ms() - data->start_time >= data->time_sleep)
	{
		
	}
}
