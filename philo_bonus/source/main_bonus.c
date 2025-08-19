/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:28:12 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/19 21:10:43 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	parse_args(int argc, char **argv, t_info *data)
{
	if (argc < 5 || argc > 6)
	{
		printf(INVALID_ARGC);
		return (false);
	}
	memset(data, 0, sizeof(t_info));
	if (!init_simulation_info(argv, data))
		return (false);
	return (true);
}

int	main(int argc, char *argv[])
{
	t_info	data;

	if (!parse_args(argc, argv, &data))
		return (EXIT_FAILURE);

}
