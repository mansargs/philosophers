/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:25:36 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/25 02:23:59 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void close_sem_and_nullify(sem_t **sem_field)
{
	sem_close(*sem_field);
	*sem_field = NULL;
}

static void	close_semaphores(t_info *data)
{
	int	i;

	if (data->stop_sem)
		close_sem_and_nullify(&data->stop_sem);
	if (data->forks_sem)
		close_sem_and_nullify(&data->forks_sem);
	if (data->print_sem)
		close_sem_and_nullify(&data->print_sem);
	i = -1;
	while (++i < data->philos_number)
	{
		if (data->philos[i].last_meal_sem)
			close_sem_and_nullify(&data->philos[i].last_meal_sem);
		if (data->philos[i].meals_eaten_sem)
			close_sem_and_nullify(&data->philos[i].meals_eaten_sem);
	}
}

static bool unlink_internal_sem(int philos_number)
{
	int		i;
	char	*name;

	i = -1;
	while (++i < philos_number)
	{
		name = individual_sem_name("/last_meal_sem", i + 1);
		if (!name)
			return (printf("\033[0;31mMemory allocation failed\033[0m"), false);
		if (sem_unlink(name) == -1 && errno == ENOENT)
			return (free(name), true);
		free(name);
		name = individual_sem_name("/meals_eaten_sem", i + 1);
		if (!name)
			return (printf("\033[0;31mMemory allocation failed\033[0m"), false);
		if (sem_unlink(name) == -1 && errno == ENOENT)
			return (free(name), true);
		free(name);
		if (errno == ENOENT)
			break ;
	}
	return (true);
}

bool	unlink_semaphores(unsigned char flag_semaphor, int philos_number)
{
	if (flag_semaphor & STOP_FLAG)
		sem_unlink("/stop_sem");
	if (flag_semaphor & FORKS_FLAG)
		sem_unlink("/forks_sem");
	if (flag_semaphor & PRINT_FLAG)
		sem_unlink("/print_sem");
	if (flag_semaphor & INTERNAL_FLAG)
		if (!unlink_internal_sem(philos_number))
			return (false);
	return (true);
}

bool	clean_all(t_info *data, unsigned char sem_flag)
{
	close_semaphores(data);
	if (!unlink_semaphores(sem_flag, data->philos_number))
		return (false);
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	free(data);
	return (true);
}
