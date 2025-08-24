/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:00:46 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/24 13:59:25 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	safe_print(t_info *data, const char *str, int index)
{
	sem_wait(data->stop_sem);
	if (!data->stop)
	{
		sem_wait(data->print_sem);
		printf("[%ld] %d %s\n", get_time_ms() - data->start_time, index, str);
		sem_post(data->print_sem);
	}
	sem_post(data->stop_sem);
}

void	one_philo_case(t_info *data)
{
	if (data->philos[0].pid == 0)
	{
		printf("[%ld] %d %s\n", get_time_ms() - data->start_time,
			data->philos[0].index, TAKE_FORK);
		usleep(data->time_die * 1000);
		printf("[%ld] %d %s\n",
			get_time_ms() - data->start_time, data->philos[0].index, DIED);
		exit(EXIT_SUCCESS);
	}
}

static void	eat(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < NEEDFUL_FORKS)
	{
		sem_wait(philo->data->forks_sem);
		safe_print(philo->data, TAKE_FORK, philo->index);
	}
	sem_wait(philo->last_meal_sem);
	philo->last_meal = get_time_ms();
	sem_post(philo->last_meal_sem);
	safe_print(philo->data, EATING, philo->index);
	smart_sleep(philo->data->time_eat, philo->data);
	i = -1;
	while (++i < NEEDFUL_FORKS)
		sem_post(philo->data->forks_sem);
	sem_wait(philo->meals_eaten_sem);
	philo->meals_eaten++;
	sem_post(philo->meals_eaten_sem);
}

static void	each_philo_routine(t_philo *philo)
{
	if (philo->pid == 0)
	{
		while (1)
		{
			sem_wait(philo->data->stop_sem);
			if (philo->data->stop)
			{
				sem_post(philo->data->stop_sem);
				break ;
			}
			sem_post(philo->data->stop_sem);
			eat(philo);
			safe_print(philo->data, SLEEPING, philo->index);
			smart_sleep(philo->data->time_sleep, philo->data);
			safe_print(philo->data, THINKING, philo->index);
		}
		exit(EXIT_SUCCESS);
	}
}

void	all_philos_routine(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_number)
		each_philo_routine(data->philos + i);
}
