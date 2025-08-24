/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:28:30 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/25 03:05:30 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>

typedef struct philosopher	t_philo;

typedef struct info
{
	long		start_time;
	int			philos_number;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			must_eat;

	sem_t		*forks_sem;
	sem_t		*print_sem;
	sem_t		*stop_sem;

	bool		stop;
	t_philo		*philos;
}				t_info;

typedef struct philosopher
{
	pid_t		pid;
	int			index;
	long		last_meal;
	int			meals_eaten;
	sem_t		*last_meal_sem;
	sem_t		*meals_eaten_sem;
	pthread_t	check_die;
	pthread_t	check_full;
	t_info		*data;
}			t_philo;

# define TAKE_FORK       "\033[0;36mhas taken a fork\033[0m"
# define EATING          "\033[0;33mis eating\033[0m"
# define SLEEPING        "\033[0;34mis sleeping\033[0m"
# define THINKING        "\033[0;35mis thinking\033[0m"
# define DIED            "\033[0;31mdied\033[0m"
# define INVALID_ARGC  	 "\033[0;31mUsage: ./philo <num> <die> <eat> <sleep> \
[must_eat]\033[0m\n"
# define SUCCESS_FINISH "\033[0;32mAll philosophers have eaten enough!\033[0m\n"

# define STOP_FLAG     1 //(1 << 0)
# define FORKS_FLAG    2 // (1 << 1)
# define PRINT_FLAG    4 // (1 << 2)
# define INTERNAL_FLAG 8
# define NEEDFUL_FORKS 2

bool	init_simulation_info(char **argv, t_info *data);

bool	convert_argc(char **argv, t_info *data);

// Time functions
long	get_time_ms(void);
void	smart_sleep(long time, t_info *data);

// Cleaning functions
bool	clean_all(t_info *data, unsigned char sem_flag);
bool	unlink_semaphores(unsigned char flag_semaphor, int philos_number);

// Utils
char	*individual_sem_name(const char *name, int num);

//Philos routine
void	one_philo_case(t_info *data);
void	all_philos_routine(t_info *data);

void	*check_full(void *arg);
void	*check_died(void *arg);

void	kill_all_childs(t_info *data);
#endif
