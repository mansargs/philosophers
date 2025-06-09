/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:22:01 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/09 15:05:02 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestamp_ms(t_timeval *tv)
{
	return (tv->tv_sec * 1000 + tv->tv_usec / 1000);
}

int	current_relative_timestamp_ms(t_info *data)
{
	t_timeval	*current;

	gettimeofday(current, NULL);
	return (timestamp_ms(current) - timestamp_ms(data->start_time));
}
