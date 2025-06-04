/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:55:51 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/04 16:05:28 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	data;
	int		i;
	if ((argc != 5 && argc != 6) || !valid_arguments(argc, (const char **) argv))
	{
		printf(INVALID_ARGC);
		return (EINVAL);
	}
	memset(&data, '\0', sizeof(t_info));
	if (!init_simulation_info(argc, (const char **) argv, &data))
		return (cleanup_data(&data), EXIT_FAILURE);
	i = -1;
	while (++i <= data.philos_num)
		pthread_join(data.threads[i].tid, NULL);
	cleanup_data(&data);
	return (EXIT_SUCCESS);
}
