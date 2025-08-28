/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:20:26 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/28 18:39:35 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_handler(void	*arg)
{
	t_philo			*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (philo->data->stop)
		{
			pthread_mutex_unlock(&philo->data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
		ready_for_eating(philo);
		eat(philo);
		smart_sleep(philo->data->time_sleep, philo->data);
		safe_print(philo->data, SLEEPING, philo->number);
		safe_print(philo->data, THINKING, philo->number);
	}
	return (NULL);
}

static bool	has_philo_died(t_philo *philo, t_info *data)
{
	long	time_since_meal;

	pthread_mutex_lock(&philo->last_eat_mutex);
	time_since_meal = get_time_ms() - philo->last_eat;
	pthread_mutex_unlock(&philo->last_eat_mutex);
	if (time_since_meal > data->time_die)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (!data->stop)
		{
			data->stop = true;
			pthread_mutex_lock(&data->print_mutex);
			printf("[%ld] %d %s\n", get_time_ms() - data->start_time,
				philo->number, DIED);
			pthread_mutex_unlock(&data->print_mutex);
		}
		pthread_mutex_unlock(&data->stop_mutex);
		return (true);
	}
	return (false);
}

void	*check_died(void *arg)
{
	t_info	*data;
	int		i;

	data = (t_info *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (data->stop)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->stop_mutex);
		i = -1;
		while (++i < data->philos_number)
			if (has_philo_died(&data->philos[i], data))
				return (NULL);
	}
	return (NULL);
}

static bool	all_philos_full(t_info *data)
{
	int		i;

	i = -1;
	while (++i < data->philos_number)
	{
		pthread_mutex_lock(&data->philos[i].counter_mutex);
		if (data->philos[i].counter < data->must_eat)
		{
			pthread_mutex_unlock(&data->philos[i].counter_mutex);
			return (false);
		}
		pthread_mutex_unlock(&data->philos[i].counter_mutex);
	}
	return (true);
}

void	*check_full(void *arg)
{
	t_info	*data;

	data = (t_info *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (data->stop)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->stop_mutex);
		if (all_philos_full(data))
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = true;
			pthread_mutex_unlock(&data->stop_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf(SUCCESS_FINISH);
			pthread_mutex_unlock(&data->print_mutex);
			break ;
		}
	}
	return (NULL);
}
