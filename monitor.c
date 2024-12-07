/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:25:25 by jgamarra          #+#    #+#             */
/*   Updated: 2024/12/06 18:37:21 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->enough_meals))
		return (false);
	elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	time_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->philos_running,
			table->philo_number))
		;
	while (!get_bool(&table->table_mutex, &table->end_simulation))
	{
		i = -1;
		while (++i < table->philo_number
			&& !get_bool(&table->table_mutex, &table->end_simulation))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				msg_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}
