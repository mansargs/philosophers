/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:13:57 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/06 14:40:52 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include <stdbool.h>

typedef struct philo t_philo;

typedef struct info
{
	long			philos_num;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			must_eat;
	long			start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		*monitors;
	bool			stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
} t_info;


struct philo
{
	t_info			*data;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		tid;
	int				index;
	int				counter;
	long			last_eat;
	pthread_mutex_t	counter_mutex;
	pthread_mutex_t	last_eat_mutex;
};

# define RED     "\033[0;31m"
# define GREEN   "\033[0;32m"
# define YELLOW  "\033[0;33m"
# define BLUE    "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN    "\033[0;36m"
# define RESET   "\033[0m "

# define TAKE_FORK CYAN "has taken a fork" RESET
# define EATING    GREEN "is eating" RESET
# define SLEEPING  BLUE "is sleeping" RESET
# define THINKING  MAGENTA "is thinking" RESET
# define DIED      RED "died" RESET
# define INVALID_ARGC RED "Usage: ./philo <num> <die> <eat> <sleep> [must_eat]\n" RESET
# define SUCCESS_FINISH GREEN "Simulation ended: all philosophers have eaten required times.\n" RESET

void	cleanup_data(t_info *data);
void	deallocation_mutexes(t_info *data, int init_count);

long	get_time_ms(void);

bool	allocation_philos_monitor(t_info *data);
bool	allocation_forks(t_info *data);
bool	init_simulation_info(const int argc, const char **argv, t_info *data);

long	ft_atol(const char *str);
bool	valid_number(const char *str);
bool	valid_arguments(const int argc, const char **argv);

void	*one_philo(void *arg);
void	*monitor_handler(void	*arg);
void	safe_print(t_info *data, const char *str, const int index);
void	*thread_handler(void *arg);

#endif
