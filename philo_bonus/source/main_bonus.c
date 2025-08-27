/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:28:12 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/27 15:52:48 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	parse_args(int argc, char **argv, t_info *data)
{
	memset(data, 0, sizeof(t_info));
	if (argc < 5 || argc > 6)
	{
		printf("%s", INVALID_ARGC);
		return (clean_all(data), false);
	}
	if (!init_simulation_info(argv, data))
		return (false);
	return (true);
}

static bool	create_philo_processes(t_info *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->philos_number)
	{
		data->philos[i].pid = fork ();
		if (data->philos[i].pid < 0)
		{
			j = -1;
			while (++j < i)
				kill(data->philos[j].pid, SIGKILL);
			return (printf("\033[0;31mChild process creating failed\033[0m\n"), false);
		}
		if (data->philos[i].pid == 0)
			each_philo_routine(data->philos + i);
	}
	return (true);
}

static bool	run_simulation(t_info *data)
{
	int	i;
	int	status;
	pid_t	ended;

	if (data->must_eat == 0)
	{
		printf(SUCCESS_FINISH);
		return (true);
	}
	i = -1;
	data->start_time = get_time_ms();
	while (++i < data->philos_number)
		data->philos[i].last_meal = data->start_time;
	if (!create_philo_processes(data))
		return (clean_all(data), false);
	// Wait until either a philosopher dies (semaphore) or any child exits
	ended = waitpid(-1, &status, 0);
	(void)ended;
	sem_post(data->has_died);
	return (true);
}

int	main(int argc, char *argv[])
{
	t_info	*data;

	data = (t_info *)malloc(sizeof(t_info));
	if (!data)
		return (EXIT_FAILURE);
	if (!parse_args(argc, argv, data))
		return (EXIT_FAILURE);
	if (!run_simulation(data))
		return (EXIT_FAILURE);
	sem_wait(data->has_died);
	kill_all_childs(data);
	return (EXIT_SUCCESS);
}
