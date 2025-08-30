/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:25:36 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/30 15:30:14 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_main_pointers(t_info *data)
{
	if (data->forks)
	{
		free (data->forks);
		data->forks = NULL;
	}
	if (data->philos)
	{
		free (data->philos);
		data->philos = NULL;
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
	pthread_mutex_destroy(&data->full_mutex);
	if (data->forks)
	{
		while (++j < init_count)
			pthread_mutex_destroy(data->forks + j);
		free(data->forks);
		data->forks = NULL;
	}
}

void	destroy_internal_mutexes(t_info *data, int up_to)
{
	int	i;

	if (!data->philos)
		return ;
	i = -1;
	while (++i < up_to)
		pthread_mutex_destroy(&data->philos[i].last_eat_mutex);
}

void	clean_all(t_info *data)
{
	destroy_internal_mutexes(data, data->philos_number);
	deallocation_forks(data, data->philos_number);
	clean_main_pointers(data);
}
