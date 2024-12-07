/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:59:43 by jgamarra          #+#    #+#             */
/*   Updated: 2024/12/07 13:18:00 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	debug_msg_status(t_philo_status philo_status,
	t_philo *philo, long elapse)
{
	if (philo_status == TAKE_FIRST_FORK
		&& !get_bool(&philo->table->table_mutex, &philo->table->end_simulation))
		printf(WHITE"%-6ld"YELLOW" %ld has taken the 1º fork [%ld]\n"RESET,
			elapse, philo->id, philo->first_fork->id);
	else if (philo_status == TAKE_SECOND_FORK
		&& !get_bool(&philo->table->table_mutex, &philo->table->end_simulation))
		printf(WHITE"%-6ld"YELLOW" %ld has taken the 2º fork [%ld]\n"RESET,
			elapse, philo->id, philo->second_fork->id);
	else if (philo_status == EATING
		&& !get_bool(&philo->table->table_mutex, &philo->table->end_simulation))
		printf(WHITE"%-6ld"CYAN" %ld is eating [ %ld of %ld ]\n"RESET,
			elapse, philo->id, philo->meals_counter, philo->table->limit_meals);
	else if (philo_status == SLEEPING
		&& !get_bool(&philo->table->table_mutex, &philo->table->end_simulation))
		printf(WHITE"%-6ld"MAGENTA" %ld is sleeping\n"RESET, elapse, philo->id);
	else if (philo_status == THINKING
		&& !get_bool(&philo->table->table_mutex, &philo->table->end_simulation))
		printf(WHITE"%-6ld"GREEN" %ld is thinking\n"RESET, elapse, philo->id);
	else if (philo_status == DIED)
		printf(WHITE"%-6ld"RED" %ld is died\n"RESET, elapse, philo->id);
}

static void	info_msg_status(t_philo_status philo_status,
	t_philo *philo, long elapse)
{
	if ((philo_status == TAKE_FIRST_FORK
			|| philo_status == TAKE_SECOND_FORK)
		&& !get_bool(&philo->table->table_mutex,
			&philo->table->end_simulation))
		printf(WHITE"%-6ld"YELLOW" %ld has taken a fork\n"RESET,
			elapse, philo->id);
	else if (philo_status == EATING
		&& !get_bool(&philo->table->table_mutex,
			&philo->table->end_simulation))
		printf(WHITE"%-6ld"CYAN" %ld is eating\n"RESET, elapse, philo->id);
	else if (philo_status == SLEEPING
		&& !get_bool(&philo->table->table_mutex,
			&philo->table->end_simulation))
		printf(WHITE"%-6ld"MAGENTA" %ld is sleeping\n"RESET,
			elapse, philo->id);
	else if (philo_status == THINKING
		&& !get_bool(&philo->table->table_mutex,
			&philo->table->end_simulation))
		printf(WHITE"%-6ld"GREEN" %ld is thinking\n"RESET,
			elapse, philo->id);
	else if (philo_status == DIED)
		printf(WHITE"%-6ld"RED" %ld is died\n"RESET, elapse, philo->id);
}

void	msg_status(t_philo_status philo_status, t_philo *philo, bool debug)
{
	long	elapse;

	elapse = gettime(MILLISECOND) - philo->table->start_simulation;
	if (get_bool(&philo->philo_mutex, &philo->enough_meals))
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		debug_msg_status(philo_status, philo, elapse);
	else
		info_msg_status(philo_status, philo, elapse);
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
