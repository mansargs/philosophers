/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:08:08 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/24 15:45:36 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	create_philos_semaphores(t_philo *philo, int num)
{
	char *name;

	name = individual_sem_name("/last_meal_sem", num);
	if (!name)
		return (printf("033[0;31mMemory allocation failed\033[0m\n"), false);
	philo->last_meal_sem = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
	free(name);
	name = individual_sem_name("/meals_eaten_sem", num);
	if (!name)
		return (printf("033[0;31mMemory allocation failed\033[0m\n"), false);
	philo->meals_eaten_sem = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
	free(name);
	if (philo->last_meal_sem == SEM_FAILED || philo->meals_eaten_sem == SEM_FAILED)
		return (printf("033[0;31mSemaphore opening failed\033[0m\n"), false);
	return (true);
}

static bool	create_philos(t_info *data)
{
	int		i;

	i = -1;
	while (++i < data->philos_number)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid < 0)
			return (printf("033[0;31Fork failed\033[0m"), false);
		data->philos[i].index = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].data = data;
		if (!create_philos_semaphores(data->philos + i, i + 1))
			return (clean_all(data, PRINT_FLAG | STOP_FLAG | FORKS_FLAG | INTERNAL_FLAG), false);
	}
	return (true);
}

static bool	allocation_data(t_info *data)
{
	data->philos = (t_philo *)malloc(sizeof (t_philo) * data->philos_number);
	if (!data->philos)
		return (clean_all(data, 0), false);
	memset(data->philos, 0, sizeof(t_philo) * data->philos_number);
	data->print_sem = sem_open("/print_sem", O_CREAT | O_EXCL, 0644, 1);
	if (data->print_sem == SEM_FAILED)
		return (printf("\033[0;31mSemaphore creating failed\033[0m\n"),
			clean_all(data, 0), false);
	if (data->philos_number > 2)
		data->forks_sem = sem_open("/forks_sem", O_CREAT | O_EXCL, 0644,
				data->philos_number - 1);
	else
		data->forks_sem = sem_open("/forks_sem", O_CREAT | O_EXCL, 0644,
				data->philos_number);
	if (data->forks_sem == SEM_FAILED)
		return (printf("\033[0;31mSemaphore creating failed\033[0m\n"),
			clean_all(data, PRINT_FLAG), false);
	data->stop_sem = sem_open("/stop_sem", O_CREAT | O_EXCL, 0644, 1);
	if (data->stop_sem == SEM_FAILED)
		return (printf("\033[0;31mSemaphore creating failed\033[0m\n"),
			clean_all(data, PRINT_FLAG | FORKS_FLAG), false);
	data->start_time = get_time_ms();
	if (!create_philos(data))
		return (false);
	return (true);
}

bool	init_simulation_info(char **argv, t_info *data)
{
	if (!convert_argc(argv, data))
		return (printf("\033[0;31mInvalid arguments\033[0m\n"),
			clean_all(data, 0), false);
	if (!allocation_data(data))
		return (false);
	return (true);
}
