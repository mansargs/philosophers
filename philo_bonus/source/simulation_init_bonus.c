/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:08:08 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/19 21:26:32 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	allocation_data(t_info *data)
{
	
}

bool	init_simulation_info(const char **argv, t_info *data)
{
	if (!convert_argc(argv, data))
		return (printf("\033[0;31mInvalid arguments\n\033[0m"), false);
	if (!allocation_data(data))
		return (false);
	return (true);
}
