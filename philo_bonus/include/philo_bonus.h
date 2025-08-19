/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:28:30 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/19 21:33:51 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS
# define PHILO_BONUS

# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct	info
{
	long			start_time;
	int				philos_number;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;

	sem_t			*forks;
	sem_t			*print_lock;
	sem_t			*stop_sem;

	t_philosopher	*philos;
}					t_info;

typedef struct	philosopher
{
	pid_t	pid;
	int		index;
	long	last_meal;
	int		meals_eaten;
	t_info	*data;

}			t_philosopher;

# define TAKE_FORK       "\033[0;36mhas taken a fork\033[0m"
# define EATING          "\033[0;33mis eating\033[0m"
# define SLEEPING        "\033[0;34mis sleeping\033[0m"
# define THINKING        "\033[0;35mis thinking\033[0m"
# define DIED            "\033[0;31mdied\033[0m"
# define INVALID_ARGC    "\033[0;31mUsage: ./philo <num> <die> <eat> <sleep>\
						 [must_eat]\n\033[0m"
# define SUCCESS_FINISH  "\033[0;32mAll philosophers\
						 have eaten enough!\n\033[0m"


bool	init_simulation_info(const char **argv, t_info *data);

bool	convert_argc(const char **argv, t_info *data);


#endif
