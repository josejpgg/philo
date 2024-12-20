/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:04:39 by jgamarra          #+#    #+#             */
/*   Updated: 2024/12/07 11:07:27 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_think;
	long	t_sleep;

	if (!pre_simulation)
		msg_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->philo_number % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

void	eating(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	msg_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	msg_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	msg_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->limit_meals > 0
		&& philo->meals_counter
		>= philo->table->limit_meals)
		set_bool(&philo->philo_mutex, &philo->enough_meals, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	sleeping(t_philo *philo)
{
	msg_status(SLEEPING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_sleep, philo->table);
}
