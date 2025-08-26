/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:08:08 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/26 20:24:48 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unlink_name_and_open(sem_t **opening_sem, const char *name, int value)
{
	sem_unlink(name);
	*opening_sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
}


static bool	create_philos_semaphores(t_philo *philo, int num)
{
	char *name;

	name = individual_sem_name("/avoid_dr", num);
	if (!name)
		return (printf("\033[0;31mMemory allocation failed\033[0m\n"), false);
	unlink_name_and_open(&philo->avoid_dr, "/avoid_dr", 1);
	free(name);
	return (true);
}

static bool	create_philos(t_info *data)
{
	int		i;

	i = -1;
	while (++i < data->philos_number)
	{
		data->philos[i].index = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		if (!create_philos_semaphores(data->philos + i, i + 1))
			return (clean_all(data), false);
	}
	i = -1;
	while (++i < data->philos_number)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid < 0)
			return (printf("\033[0;31mFork failed\033[0m"), false);
	}
	return (true);
}

static bool	allocation_data(t_info *data)
{
	data->philos = (t_philo *)malloc(sizeof (t_philo) * data->philos_number);
	if (!data->philos)
		return (clean_all(data), false);
	memset(data->philos, 0, sizeof(t_philo) * data->philos_number);
	unlink_name_and_open(&data->print_sem, "/print_sem", 1);
	if (data->philos_number > 2)
		unlink_name_and_open(&data->forks_sem, "/forks_sem", data->philos_number - 1);
	else
		unlink_name_and_open(&data->forks_sem, "/forks_sem", data->philos_number);
	unlink_name_and_open(&data->stop_sem, "/stop_sem", 1);
	unlink_name_and_open(&data->has_died, "/has_died", 0);
	unlink_name_and_open(&data->is_full, "/is_full", 0);
	if (data->print_sem == SEM_FAILED || data->forks_sem == SEM_FAILED
		|| data->stop_sem == SEM_FAILED || data->is_full == SEM_FAILED
		|| data->has_died == SEM_FAILED)
		return (printf("\033[0;31mSemaphore creating failed\033[0m\n"), clean_all(data), false);
	if (!create_philos(data))
		return (false);
	return (true);
}

bool	init_simulation_info(char **argv, t_info *data)
{
	if (!convert_argc(argv, data))
		return (printf("\033[0;31mInvalid arguments\033[0m\n"), clean_all(data), false);
	if (!allocation_data(data))
		return (false);
	return (true);
}
