/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:25:36 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/23 13:00:36 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	close_semaphores(t_info *data)
{
	if (data->stop_sem)
	{
		sem_close(data->stop_sem);
		data->stop_sem = NULL;
	}
	if (data->forks_sem)
	{
		sem_close(data->forks_sem);
		data->forks_sem = NULL;
	}
	if (data->print_sem)
	{
		sem_close(data->print_sem);
		data->print_sem = NULL;
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
