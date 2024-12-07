/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:18:21 by jgamarra          #+#    #+#             */
/*   Updated: 2024/12/07 11:07:01 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "lib/libft/libft.h"
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <string.h> // memset
# include <unistd.h> // write, usleep
# include <stdbool.h> // bool
# include <sys/time.h> // gettimeofday
# include <limits.h> // INT_MAX
# include <pthread.h> // mutex threads
# include <errno.h> // errno
# define WHITE "\033[37m"  // ANSI escape code for white text
# define RESET "\033[0m" // ANSI escape code to reset text formatting
# define RED "\033[31m" // RED
# define CYAN "\033[1;36m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define MAGENTA "\033[1;35m"

# define DEBUG_MODE 0

typedef pthread_mutex_t	t_mutex;
typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

typedef enum e_action
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_action;

typedef enum e_time_action
{
	MILLISECOND,
	MICROSECOND,
}	t_time_action;


typedef struct s_fork
{
	t_mutex	fork;
	long	id;
}	t_fork;

typedef struct s_table
{
	long		philo_number;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		limit_meals;
	long		start_simulation;
	bool		end_simulation;
	bool		philos_ready;
	long		philos_running;
	pthread_t	monitor;
	t_mutex		table_mutex;
	t_mutex		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
}	t_table;

typedef struct s_philo
{
	long		id;
	long		meals_counter;
	bool		enough_meals;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mutex		philo_mutex;
	t_table		*table;
}	t_philo;

int		process_initial_args(int argc, char **argv, t_table *initial);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_action action);
void	safe_mutex_handle(t_mutex *mutex, t_action action);
void	*safe_malloc(size_t size);
void	set_bool(t_mutex *mutex, bool *dest, bool value);
bool	get_bool(t_mutex *mutex, bool *dest);
void	set_long(t_mutex *mutex, long *dest, long value);
long	get_long(t_mutex *mutex, long *dest);
void	wait_all_philos(t_table *table);
long	gettime(t_time_action time_action);
void	precise_usleep(long usec, t_table *table);
void	msg_status(t_philo_status philo_status, t_philo *philo, bool debug);
void	dinner_start(t_table *table);
bool	all_threads_running(t_mutex *mutex, long *philos_running, long philos);
void	increase_long(t_mutex *mutex, long *value);
void	*monitor_dinner(void *data);
void	clean(t_table *table);
void	de_synchronize_philos(t_philo *philo);
void	thinking(t_philo *philo, bool pre_simulation);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);

#endif
