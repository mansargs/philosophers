/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:37:26 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/26 21:00:36 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all_childs(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_number)
		kill(data->philos[i].pid, SIGKILL);
}

static bool	has_philo_died(t_philo *philo, t_info *data)
{
	long	time_since_meal;

	sem_wait(philo->avoid_dr);
	time_since_meal = get_time_ms() - philo->last_meal;
	sem_post(philo->avoid_dr);
	if (time_since_meal > data->time_die)
	{
		sem_wait(data->stop_sem);
		if (!data->stop)
		{
			data->stop = true;
			// kill_all_childs(data);
			sem_wait(data->print_sem);
			printf("[%ld] %d %s\n", get_time_ms() - data->start_time,
				philo->index, DIED);
			sem_post(data->print_sem);
		}
		sem_post(data->stop_sem);
		return (true);
	}
	return (false);
}

void	*check_died(void *arg)
{
	t_philo	*philo;
	t_info	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		usleep(1000);
		sem_wait(data->stop_sem);
		if (data->stop)
		{
			sem_post(data->stop_sem);
			break ;
		}
		sem_post(data->stop_sem);
		// i = -1;
		// while (++i < data->philos_number)
			if (has_philo_died(philo, data))
				return (NULL);
	}
	return (NULL);
}

static bool	all_philos_full(t_info *data, t_philo *philo)
{
	// int		i;

	// i = -1;
	// while (++i < data->philos_number)
	// {
		sem_wait(philo->meals_eaten_sem);
		if (philo->meals_eaten < data->must_eat)
		{
			sem_post(philo->meals_eaten_sem);
			return (false);
		}
		sem_post(philo->meals_eaten_sem);
	// }
	return (true);
}

void	*check_full(void *arg)
{
	t_philo	*philo;
	t_info	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		sem_wait(data->stop_sem);
		if (data->stop)
		{
			sem_post(data->stop_sem);
			break ;
		}
		sem_post(data->stop_sem);
		if (all_philos_full(data, philo))
		{
			sem_wait(data->stop_sem);
			data->stop = true;
			sem_post(data->stop_sem);
			sem_wait(data->print_sem);
			printf("%s\n", SUCCESS_FINISH);
			sem_post(data->print_sem);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
