/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:25:36 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/24 14:09:48 by mansargs         ###   ########.fr       */
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
			
	}
}

static void	unlink_semaphores(unsigned char flag_semaphor)
{
	if (flag_semaphor & STOP_FLAG)
		sem_unlink("/stop_sem");
	if (flag_semaphor & FORKS_FLAG)
		sem_unlink("/forks_sem");
	if (flag_semaphor & PRINT_FLAG)
		sem_unlink("/print_sem");
}

void	clean_all(t_info *data, unsigned char sem_flag)
{
	close_semaphores(data);
	unlink_semaphores(sem_flag);
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	free(data);
}
