/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:08:08 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/23 15:09:43 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	create_philos(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_number)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid < 0)
		{
			printf("033[0;31Fork failed\033[0m");
			return (false);
		}
		data->philos[i].index = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].data = data;
	}
	return (true);
}

static bool	allocation_data(t_info *data)
{
	data->philos = (t_philo *)malloc(sizeof (t_philo) * data->philos_number);
	if (!data->philos)
		return (clean_all(data, 0), false);
	data->print_sem = sem_open("/print_sem", O_CREAT | O_EXCL, 0644, 1);
	if (data->print_sem == SEM_FAILED)
		return (printf("\033[0;31mSemaphore creating failed\n\033[0m"),
			clean_all(data, 0), false);
	if (data->philos_number > 2)
		data->forks_sem = sem_open("/forks_sem", O_CREAT | O_EXCL, 0644,
				data->philos_number - 1);
	else
		data->forks_sem = sem_open("/forks_sem", O_CREAT | O_EXCL, 0644,
				data->philos_number);
	if (data->forks_sem == SEM_FAILED)
		return (printf("\033[0;31mSemaphore creating failed\n\033[0m"),
			clean_all(data, PRINT_FLAG), false);
	data->stop_sem = sem_open("/stop_sem", O_CREAT | O_EXCL, 0644, 1);
	if (data->stop_sem == SEM_FAILED)
		return (printf("\033[0;31mSemaphore creating failed\n\033[0m"),
			clean_all(data, PRINT_FLAG | FORKS_FLAG), false);
	data->start_time = get_time_ms();
	if (!create_philos(data))
		return (clean_all(data, PRINT_FLAG | STOP_FLAG | FORKS_FLAG), false);
	return (true);
}

bool	init_simulation_info(char **argv, t_info *data)
{
	if (!convert_argc(argv, data))
		return (printf("\033[0;31mInvalid arguments\n\033[0m"),
			clean_all(data, 0), false);
	if (!allocation_data(data))
		return (false);
	return (true);
}
