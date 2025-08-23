/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:13:57 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/21 19:26:44 by mansargs         ###   ########.fr       */
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

typedef struct philo	t_philo;

typedef struct info
{
	long			start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		*monitors;
	int				philos_number;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	bool			stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
}					t_info;

typedef struct philo
{
	long			last_eat;
	t_info			*data;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int				number;
	int				counter;
	pthread_t		tid;
	pthread_mutex_t	counter_mutex;
	pthread_mutex_t	last_eat_mutex;
}					t_philo;

# define TAKE_FORK       "\033[0;36mhas taken a fork\033[0m"
# define EATING          "\033[0;33mis eating\033[0m"
# define SLEEPING        "\033[0;34mis sleeping\033[0m"
# define THINKING        "\033[0;35mis thinking\033[0m"
# define DIED            "\033[0;31mdied\033[0m"
# define INVALID_ARGC    "\033[0;31mUsage: ./philo <num> <die> <eat> <sleep>\
						 [must_eat]\n\033[0m"
# define SUCCESS_FINISH  "\033[0;32mAll philosophers\
						 have eaten enough!\n\033[0m"

// time functions
long	get_time_ms(void);
void	smart_sleep(long time, t_info *data);

// read arguments
bool	convert_argc(const char **argv, t_info *data);

// Creation and initialize
bool	init_simulation_info(char **argv, t_info *data);
bool	create_threads(t_info *data);

//cleaning functions
void	clean_all(t_info *data);
void	destroy_internal_mutexes(t_info *data, int up_to);
void	deallocation_forks(t_info *data, int init_count);
void	clean_main_pointers(t_info *data);

// Philosophers actions and one philosopher case
void	safe_print(t_info *data, const char *str, int index);
void	*one_philo(void *arg);
void	ready_for_eating(t_philo *philo);
void	eat(t_philo *philo);

//Thread handler  functions
void	*check_full(void *arg);
void	*check_died(void *arg);
void	*thread_handler(void	*arg);
void	*one_philo(void *arg);

#endif
