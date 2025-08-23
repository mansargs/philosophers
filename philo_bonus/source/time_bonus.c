/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:22:01 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/23 15:21:19 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	smart_sleep(long time, t_info *data)
{
	long	start;

	start = get_time_ms();
	while (1)
	{
		sem_wait(data->stop_sem);
		if (data->stop)
		{
			sem_post(data->stop_sem);
			break ;
		}
		sem_post(data->stop_sem);
		if (get_time_ms() - start >= time)
			break ;
		usleep(100);
	}
}
