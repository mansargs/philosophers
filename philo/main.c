/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:55:51 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/09 15:11:01 by mansargs         ###   ########.fr       */
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
		return (clean_main_pointers(&data), EXIT_FAILURE);
	if (!create_threads(data))
		return (clean_all(&data), EXIT_FAILURE);
	i = -1;
	if (data.philos_number != 1)
	{
		pthread_join(data.monitors[0], NULL);
		if (data.must_eat != -1)
			pthread_join(data.monitors[1], NULL);
	}
	while (++i < data.philos_number)
		pthread_join(data.philos[i].tid, NULL);
	clean_all(&data);
	return (EXIT_SUCCESS);
}
