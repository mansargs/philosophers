/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:54:59 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/30 15:42:00 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_print(t_info *data, const char *str, int index)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (!data->stop)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("[%ld] %d %s\n", get_time_ms() - data->start_time, index, str);
		pthread_mutex_unlock(&data->print_mutex);
	}
	pthread_mutex_unlock(&data->stop_mutex);
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	printf("[%ld] %d %s\n", get_time_ms() - philo->data->start_time,
		philo->number, TAKE_FORK);
	usleep(philo->data->time_die * 1000);
	printf("[%ld] %d %s\n",
		get_time_ms() - philo->data->start_time, philo->number, DIED);
	return (NULL);
}

void ready_for_eating(t_philo *philo)
{
    pthread_mutex_t *first;
    pthread_mutex_t *second;

    // Always pick the lower-numbered fork first to prevent deadlock
    if (philo->number % 2 == 0)
    {
        first = philo->left;
        second = philo->right;
    }
    else
    {
        first = philo->right;
        second = philo->left;
    }

    pthread_mutex_lock(first);
    safe_print(philo->data, TAKE_FORK, philo->number);
    pthread_mutex_lock(second);
    safe_print(philo->data, TAKE_FORK, philo->number);
}


static void release_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left);
    pthread_mutex_unlock(philo->right);
}


void	eat(t_philo *philo)
{
	ready_for_eating(philo);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_time_ms();
	pthread_mutex_unlock(&philo->last_eat_mutex);
	safe_print(philo->data, EATING, philo->number);
	smart_sleep(philo->data->time_eat, philo->data);
	release_forks(philo);
	philo->counter++;
	if (philo->counter == philo->data->must_eat)
	{
		pthread_mutex_lock(&philo->data->full_mutex);
		philo->data->is_full++;
		pthread_mutex_unlock(&philo->data->full_mutex);
	}
}
