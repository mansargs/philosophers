/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:20:26 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/28 17:48:35 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_handler(void *arg)
{
	t_info	*data = (t_info *)arg;
	pthread_mutex_lock(data->forks + data->philos)
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_info			data;
	unsigned int	i;

	if (argc < 5 || argc > 6 || !valid_arguments(argc, argv))
	{
		printf(INVALID_ARGC);
		return (EINVAL);
	}
	if (!init_simulation_info(argc, (const char **)argv, &data))
		return (EXIT_FAILURE);
	i = 0;
	while (i < data.philos_num)
	{
		pthread_join(data.philos[i].tid, NULL);
		++i;
	}

	free(data.philos);
	return (EXIT_SUCCESS);
}
