/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:25:36 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/27 15:08:58 by mansargs         ###   ########.fr       */
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

	if (data->forks_sem)
		close_sem_and_nullify(&data->forks_sem);
	if (data->print_sem)
		close_sem_and_nullify(&data->print_sem);
	if (data->is_full)
		close_sem_and_nullify(&data->is_full);
	if (data->has_died)
		close_sem_and_nullify(&data->has_died);
	i = -1;
	while (++i < data->philos_number)
	{
		if (data->philos[i].avoid_dr)
			close_sem_and_nullify(&data->philos[i].avoid_dr);
	}
}

bool	unlink_semaphores(int philos_number)
{
	int		i;
	char	*name;

	sem_unlink("/forks_sem");
	sem_unlink("/print_sem");
	sem_unlink("/has_died");
	sem_unlink("/is_full");
	i = -1;
	while (++i < philos_number)
	{
		name = individual_sem_name("/avoid_dr", i + 1);
		if (!name)
			return (printf("\033[0;31mMemory allocation failed\033[0m"), false);
		sem_unlink(name);
		free(name);
		if (errno == ENOENT)
			break ;
	}
	return (true);
}

bool	clean_all(t_info *data)
{
	close_semaphores(data);
	if (!unlink_semaphores(data->philos_number))
		return (false);
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	free(data);
	return (true);
}
