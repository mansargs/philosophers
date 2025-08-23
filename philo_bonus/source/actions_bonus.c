/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:00:46 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/23 15:25:17 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	safe_print(t_info *data, const char *str, int index)
{
	sem_wait(data->stop_sem);
	if (!data->stop)
	{
		sem_wait(data->print_sem);
		printf("[%ld] %d %s\n", get_time_ms() - data->start_time, index, str);
		sem_post(data->print_sem);
	}
	sem_post(data->stop_sem);
}

void	one_philo_case(t_info *data)
{
	if (data->philos[0].pid == 0)
	{
		printf("[%ld] %d %s\n", get_time_ms() - data->start_time,
			data->philos[0].index, TAKE_FORK);
		usleep(data->time_die * 1000);
		printf("[%ld] %d %s\n",
			get_time_ms() - data->start_time, data->philos[0].index, DIED);
		exit(EXIT_SUCCESS);
	}
}
