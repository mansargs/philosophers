/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:25:36 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/06 14:50:44 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

	void	cleanup_data(t_info *data)
	{
		if (data->forks)
		{
			free (data->forks);
			data->forks = NULL;
		}
		if (data->threads)
		{
			free (data->threads);
			data->threads = NULL;
		}
		if (data->monitors)
		{
			free (data->monitors);
			data->monitors = NULL;
		}
	}

void	deallocation_forks(t_info *data, int init_count)
{
	int	j;

	j = -1;
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	while (++j < init_count)
		pthread_mutex_destroy(data->forks + j);
	free(data->forks);
	data->forks = NULL;
}
