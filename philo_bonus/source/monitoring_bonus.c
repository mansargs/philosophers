/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:37:26 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/28 04:27:39 by mansargs         ###   ########.fr       */
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

void	*check_died(void *arg)
{
	t_philo	*philo;
	t_info	*data;
	long	time_since_meal;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		sem_wait(philo->avoid_dr);
		time_since_meal = get_time_ms() - philo->last_meal;
		sem_post(philo->avoid_dr);
		if (time_since_meal > data->time_die)
		{
			sem_wait(data->print_sem);
			printf("[%ld] %d %s\n", get_time_ms() - data->start_time,
				philo->index, DIED);
			sem_post(data->has_died);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*check_full(void *arg)
{
	t_info	*data;
	int		i;

	data = (t_info *) arg;
	i = -1;
	while (++i < data->philos_number)
		sem_wait(data->is_full);
	usleep(1000);
	kill_all_childs(data);
	sem_wait(data->print_sem);
	printf(SUCCESS_FINISH);
	return (NULL);
}
