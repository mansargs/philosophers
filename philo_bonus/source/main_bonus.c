/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:28:12 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/23 15:38:52 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	parse_args(int argc, char **argv, t_info *data)
{
	memset(data, 0, sizeof(t_info));
	if (argc < 5 || argc > 6)
	{
		printf("%s", INVALID_ARGC);
		return (clean_all(data, 0), false);
	}
	if (!init_simulation_info(argv, data))
		return (false);
	return (true);
}
// static void	run_simulation(t_info *data)
// {
// 	if (data->must_eat == 0)
// 		return (printf(SUCCESS_FINISH), true);
// 	if (data->philos_number == 1)

// }

int	main(int argc, char *argv[])
{
	t_info	*data;

	data = (t_info *)malloc(sizeof(t_info));
	if (!data)
		return (EXIT_FAILURE);
	if (!parse_args(argc, argv, data))
		return (EXIT_FAILURE);
	clean_all(data, STOP_FLAG | PRINT_FLAG | FORKS_FLAG);
	return (EXIT_SUCCESS);
}
