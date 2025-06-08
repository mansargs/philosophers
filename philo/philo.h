/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:13:57 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/08 22:39:27 by mansargs         ###   ########.fr       */
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

typedef struct timeval t_timeval;
typedef struct philo t_philo;

typedef struct info
{
	int				philos_number;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	bool			stop;
	t_timeval		*start_time;
	t_philo			*philos;
	pthread_t		*monitors;
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
} t_info;

typedef struct philo
{
	int				number;
	int				counter;
	t_timeval		*last_eat;
	t_info			*data;
	pthread_t		tid;
	pthread_mutex_t	counter_mutex;
	pthread_mutex_t	last_eat_mutex;
} t_philo;

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

long	get_time_ms(void);

void		*check_full(void *arg);
void		*check_died(void *arg);
void		*thread_handler(void	*arg);
void		eat(t_philo *philo);
void		ready_for_eating(t_philo *philo);
void		*one_philo(void *arg);
void	cleanup_data(t_info *data);

void destroy_internal_mutexes(t_info *data, int up_to);
bool allocation_philos_monitor(t_info *data);
void	deallocation_forks(t_info *data, int init_count);
bool	init_simulation_info(const int argc, const char **argv, t_info *data);
void	smart_sleep(long duration_ms);

#endif
