/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:00:46 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/30 21:06:21 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	safe_print(t_info *data, const char *str, int index)
{
	sem_wait(data->print_sem);
	printf("[%ld] %d %s\n", get_time_ms() - data->start_time, index, str);
	sem_post(data->print_sem);
}

static void	eat(t_philo *philo)
{
	int	i;

	sem_wait(philo->data->secure);
	i = -1;
	while (++i < NEEDFUL_FORKS)
	{
		sem_wait(philo->data->forks_sem);
		safe_print(philo->data, TAKE_FORK, philo->index);
	}
	safe_print(philo->data, EATING, philo->index);
	sem_wait(philo->avoid_dr);
	philo->last_meal = get_time_ms();
	sem_post(philo->avoid_dr);
	smart_sleep(philo->data->time_eat);
	i = -1;
	while (++i < NEEDFUL_FORKS)
		sem_post(philo->data->forks_sem);
	sem_post(philo->data->secure);
	sem_wait(philo->avoid_dr);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->data->must_eat)
		sem_post(philo->data->is_full);
	sem_post(philo->avoid_dr);
}

void	each_philo_routine(t_philo *philo)
{
	if (pthread_create(&philo->check_die, NULL, check_died, philo) != 0)
	{
		printf("\033[0;31mMonitor creating failed\033[0m\n");
		clean_all(philo->data, false);
		exit (EXIT_FAILURE);
	}
	pthread_detach(philo->check_die);
	while (1)
	{
		eat(philo);
		safe_print(philo->data, SLEEPING, philo->index);
		smart_sleep(philo->data->time_sleep);
		safe_print(philo->data, THINKING, philo->index);
		usleep(100);
	}
	exit(EXIT_SUCCESS);
}
