/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:55:51 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/30 15:29:21 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	parse_args(int argc, char **argv, t_info *data)
{
	memset(data, 0, sizeof(t_info));
	if (argc < 5 || argc > 6)
	{
		printf("%s %s", INVALID_ARGC, EXPECTED_ARGC);
		return (false);
	}
	if (!init_simulation_info(argv, data))
		return (false);
	return (true);
}

static int	run_simulation(t_info *data)
{
	int	i;

	if (!data->must_eat)
		return (printf(SUCCESS_FINISH), EXIT_SUCCESS);
	if (!create_threads(data))
		return (clean_all(data), EXIT_FAILURE);
	if (data->philos_number != 1)
	{
		pthread_join(data->monitors[0], NULL);
		if (data->must_eat != -1)
			pthread_join(data->monitors[1], NULL);
	}
	i = -1;
	while (++i < data->philos_number)
		pthread_join(data->philos[i].tid, NULL);
	clean_all(data);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_info	data;
	int		res;

	if (!parse_args(argc, argv, &data))
		return (clean_main_pointers(&data), EXIT_FAILURE);
	res = run_simulation(&data);
	if (res == EXIT_FAILURE)
		return (EXIT_FAILURE);
	clean_all(&data);
	return (res);
}
