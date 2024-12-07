/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:43:53 by jgamarra          #+#    #+#             */
/*   Updated: 2024/12/06 22:57:45 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_philos(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->philos_ready))
		;
}

bool	all_threads_running(t_mutex *mutex, long *philos_running, long philos)
{
	bool	result;

	result = false;
	safe_mutex_handle(mutex, LOCK);
	if (*philos_running == philos)
		result = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (result);
}

void	increase_long(t_mutex *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

void	de_synchronize_philos(t_philo *philo)
{
	if (philo->table->philo_number % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2 == 0)
			thinking(philo, true);
	}
}
