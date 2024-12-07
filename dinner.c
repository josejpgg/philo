/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:11:10 by jgamarra          #+#    #+#             */
/*   Updated: 2024/12/07 12:29:08 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_alone(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_philos(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex, &philo->table->philos_running);
	msg_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!get_bool(&philo->table->table_mutex, &philo->table->end_simulation))
		usleep(200);
	return (NULL);
}

void	*dinner_multiple(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_philos(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex, &philo->table->philos_running);
	de_synchronize_philos(philo);
	while (!get_bool(&philo->table->table_mutex, &philo->table->end_simulation))
	{
		if (get_bool(&philo->philo_mutex, &philo->enough_meals))
			break ;
		eating(philo);
		sleeping(philo);
		thinking(philo, false);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->limit_meals == 0)
		return ;
	else if (table->philo_number == 1)
		safe_thread_handle(&table->philos[0].thread_id, dinner_alone,
			&table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_number)
			safe_thread_handle(&table->philos[i].thread_id, dinner_multiple,
				&table->philos[i], CREATE);
	}
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	table->start_simulation = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->philos_ready, true);
	i = -1;
	while (++i < table->philo_number)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
