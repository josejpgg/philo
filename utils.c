/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:59:50 by jgamarra          #+#    #+#             */
/*   Updated: 2024/12/06 18:43:41 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(t_time_action time_action)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		ft_exit_message("gettimeofday failed", 1);
	if (time_action == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_action == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		ft_exit_message("wrong action", 1);
	return (1);
}

void	precise_usleep(long sleep_time, t_table *table)
{
	long	start;
	long	elapse;
	long	remaining;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < sleep_time)
	{
		if (get_bool(&table->table_mutex, &table->end_simulation))
			break ;
		elapse = gettime(MICROSECOND) - start;
		remaining = sleep_time - elapse;
		if (remaining > 1e3)
			usleep (remaining / 2);
		else
		{
			while (gettime(MICROSECOND) - start < sleep_time)
				;
		}
	}
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	philo = table->philos;
	i = -1;
	while (++i < table->philo_number)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->write_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}
