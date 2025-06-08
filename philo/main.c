/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:55:51 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/08 22:39:47 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	data;
	int		i;

	if (argc < 5 || argc > 6)
	{
		printf(INVALID_ARGC);
		return (EINVAL);
	}
	memset(&data, '\0', sizeof(t_info));
	if (!init_simulation_info(argc, (const char **) argv, &data))
		return (cleanup_data(&data), EXIT_FAILURE);
	i = -1;
	if (data.philos_num != 1)
	{
		pthread_join(data.monitors[0], NULL);
		pthread_join(data.monitors[1], NULL);
	}
	while (++i < data.philos_num)
		pthread_join(data.philos[i].tid, NULL);
	usleep(5000);
	deallocation_forks(&data, data.philos_num);
	destroy_internal_mutexes(&data, data.philos_num);
	cleanup_data(&data);
	return (EXIT_SUCCESS);
}
