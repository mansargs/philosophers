/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:13:57 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/28 15:12:20 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <errno.h>
# include <stdbool.h>

typedef struct	philo
{
	unsigned int	index;
	pthread_t		tid;
}					t_philo;


typedef struct		info
{
	unsigned int	philos_num;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	int				eat_limit;
	t_philo			*philos;
}					t_info;


# define TAKE_FORK "has taken a work"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"
# define INVALID_ARGC "\033[31mYou need to run the program like this\n./philo number_of_philosopher time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\033[0m\n"


int		ft_atoi(const char *str);
bool	valid_number(const char *str);
bool	valid_arguments(int argc, char **argv);

#endif
