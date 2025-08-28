/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:08:08 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/28 03:52:34 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	unlink_name_and_open(sem_t **opening_sem, const char *name, int value)
{
	sem_unlink(name);
	*opening_sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (*opening_sem == SEM_FAILED)
		return (printf("\033[0;31mSemaphore creating failed\033[0m\n"), false);
	return (true);
}

static bool	init_philos_semaphores(t_philo *philo, int num)
{
	char	*name;
	bool	res;

	name = individual_sem_name("/avoid_dr", num);
	if (!name)
		return (printf("\033[0;31mMemory allocation failed\033[0m\n"), false);
	res = unlink_name_and_open(&philo->avoid_dr, name, 1);
	free(name);
	return (res);
}

static bool	init_philos_data(t_info *data)
{
	int		i;

	i = -1;
	while (++i < data->philos_number)
	{
		data->philos[i].index = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		if (!init_philos_semaphores(data->philos + i, i + 1))
			return (false);
	}
	return (true);
}

static bool	allocation_data(t_info *data)
{
	data->philos = (t_philo *)malloc(sizeof (t_philo) * data->philos_number);
	if (!data->philos)
		return (clean_all(data, true), false);
	memset(data->philos, 0, sizeof(t_philo) * data->philos_number);
	if (unlink_name_and_open(&data->print_sem, "/print_sem", 1) == false)
		return (false);
	if (data->philos_number > 2
		&& !unlink_name_and_open(&data->forks_sem, "/forks_sem",
			data->philos_number - 1))
		return (false);
	else if (!unlink_name_and_open(&data->forks_sem, "/forks_sem",
			data->philos_number))
		return (false);
	if (unlink_name_and_open(&data->has_died, "/has_died", 0) == false)
		return (false);
	if (unlink_name_and_open(&data->is_full, "/is_full", 0) == false)
		return (false);
	if (!init_philos_data(data))
		return (false);
	return (true);
}

bool	init_simulation_info(char **argv, t_info *data)
{
	if (!convert_argc(argv, data))
		return (printf("\033[0;31mInvalid arguments\033[0m\n"),
			free(data), false);
	if (!allocation_data(data))
		return (clean_all(data, true), false);
	return (true);
}
