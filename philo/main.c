/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:20:26 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/02 21:36:25 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_handler(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		if (philo->index % 2 == 1)
		{
			pthread_mutex_lock(philo->right);
			printf(TAKE_FORK, philo->index);
			pthread_mutex_lock(philo->left);
			printf(TAKE_FORK, philo->index);
		}
		else
		{
			pthread_mutex_lock(philo->left);
			printf(TAKE_FORK, philo->index);
			pthread_mutex_lock(philo->right);
			printf(TAKE_FORK, philo->index);
		}
		printf(EATING, philo->index);
		usleep(philo->data->time_eat);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		printf(SLEEPING, philo->index);
		usleep(philo->data->time_sleep);
		printf(THINKING, philo->index);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_info			data;
	unsigned int	i;

	if (argc < 5 || argc > 6 || !valid_arguments(argc, argv))
	{
		printf(INVALID_ARGC);
		return (EINVAL);
	}
	if (!init_simulation_info(argc, (const char **)argv, &data))
		return (EXIT_FAILURE);
	i = 0;
	while (i < data.philos_num)
	{
		pthread_join(data.philos[i].tid, NULL);
		++i;
	}
	free(data.philos);
	return (EXIT_SUCCESS);
}
