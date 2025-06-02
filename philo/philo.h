/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:13:57 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/02 21:30:05 by mansargs         ###   ########.fr       */
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

typedef struct philo t_philo;

typedef struct info
{
	unsigned int	philos_num;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	int				eat_limit;
	t_philo			*philos;
	pthread_mutex_t	*forks;
} t_info;

struct philo
{
	unsigned int	index;
	pthread_t		tid;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_info			*data;
};

# define RED     "\033[0;31m"
# define GREEN   "\033[0;32m"
# define YELLOW  "\033[0;33m"
# define BLUE    "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN    "\033[0;36m"
# define RESET   "\033[0m"

# define TAKE_FORK CYAN "%d has taken a fork\n" RESET
# define EATING    GREEN "%d is eating\n" RESET
# define SLEEPING  BLUE "%d is sleeping\n" RESET
# define THINKING  MAGENTA "%d is thinking\n" RESET
# define DIED      RED "%d died\n" RESET
# define INVALID_ARGC RED "Usage: ./philo <num> <die> <eat> <sleep> [must_eat]\n" RESET



int		ft_atoi(const char *str);
bool	valid_number(const char *str);
bool	valid_arguments(int argc, char **argv);
void	deallocation_mutexes(pthread_mutex_t *forks, unsigned int index);
bool	allocation_philos(t_info *data);
bool	allocation_mutexes(t_info *data);
bool	init_simulation_info(const int argc, const char **argv, t_info *data);
void	*thread_handler(void *arg);

#endif
