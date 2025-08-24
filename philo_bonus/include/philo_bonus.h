/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:28:30 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/24 13:57:32 by mansargs         ###   ########.fr       */
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
	pid_t	pid;
	int		index;
	long	last_meal;
	int		meals_eaten;
	sem_t	*last_meal_sem;
	sem_t	*meals_eaten_sem;
	t_info	*data;
}			t_philo;

# define TAKE_FORK       "\033[0;36mhas taken a fork\033[0m"
# define EATING          "\033[0;33mis eating\033[0m"
# define SLEEPING        "\033[0;34mis sleeping\033[0m"
# define THINKING        "\033[0;35mis thinking\033[0m"
# define DIED            "\033[0;31mdied\033[0m"
# define INVALID_ARGC  	 "\033[0;31mUsage: ./philo <num> <die> <eat> <sleep> \
[must_eat]\033[0m\n"
# define SUCCESS_FINISH "\033[0;32mAll philosophers have eaten enough!\n\033[0m"

# define STOP_FLAG     1 //(1 << 0)
# define FORKS_FLAG    2 // (1 << 1)
# define PRINT_FLAG    4 // (1 << 2)
# define NEEDFUL_FORKS 2

bool	init_simulation_info(char **argv, t_info *data);

bool	convert_argc(char **argv, t_info *data);

// Time functions
long	get_time_ms(void);
void	smart_sleep(long time, t_info *data);

// Cleaning functions
void	clean_all(t_info *data, unsigned char sem_flag);

// Utils
char	*individual_sem_name(const char *name, int num);

//Philos routine
void	one_philo_case(t_info *data);
void	all_philos_routine(t_info *data);

#endif
