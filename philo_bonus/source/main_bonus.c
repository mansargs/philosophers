/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:28:12 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/25 03:06:29 by mansargs         ###   ########.fr       */
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
static void	run_simulation(t_info *data)
{
	int	i;

	if (data->must_eat == 0)
	{
		printf(SUCCESS_FINISH);
		return ;
	}
	if (data->philos_number == 1)
		one_philo_case(data);
	else
		all_philos_routine(data);
	i = -1;
	while (++i < data->philos_number)
		waitpid(data->philos[i].pid, NULL, 0);
}

int	main(int argc, char *argv[])
{
	t_info	*data;

	data = (t_info *)malloc(sizeof(t_info));
	if (!data)
		return (EXIT_FAILURE);
	if (!parse_args(argc, argv, data))
		return (EXIT_FAILURE);
	run_simulation(data);
	kill_all_childs(data);
	if (!clean_all(data, STOP_FLAG | PRINT_FLAG | FORKS_FLAG | INTERNAL_FLAG))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
