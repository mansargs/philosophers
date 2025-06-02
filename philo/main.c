/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:20:26 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/03 01:44:59 by mansargs         ###   ########.fr       */
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
	while (1)
	{
		if (philo->index % 2 == 1)
		{
			pthread_mutex_lock(philo->right);
			printf(TAKE_FORK, get_time_ms() - philo->data->simulation_start, philo->index);
			pthread_mutex_lock(philo->left);
			printf(TAKE_FORK, get_time_ms() - philo->data->simulation_start, philo->index);
		}
		else
		{
			pthread_mutex_lock(philo->left);
			printf(TAKE_FORK, get_time_ms() - philo->data->simulation_start, philo->index);
			pthread_mutex_lock(philo->right);
			printf(TAKE_FORK, get_time_ms() - philo->data->simulation_start, philo->index);
		}
		printf(EATING, get_time_ms() - philo->data->simulation_start, philo->index);
		++philo->counter;
		usleep(philo->data->time_eat);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		printf(SLEEPING, get_time_ms() - philo->data->simulation_start, philo->index);
		usleep(philo->data->time_sleep);
		printf(THINKING, get_time_ms() - philo->data->simulation_start, philo->index);
	}
	return (NULL);
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	printf(TAKE_FORK, get_time_ms() - philo->data->simulation_start, philo->index);
	usleep(philo->data->time_die + 10);
	printf(DIED, get_time_ms() - philo->data->simulation_start, philo->index);
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
	while (i < data.philos_num)
		pthread_join(data.philos[i].tid, NULL);
	free(data.philos);
	return (EXIT_SUCCESS);
}
