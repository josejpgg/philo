/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:13:01 by jgamarra          #+#    #+#             */
/*   Updated: 2024/12/06 18:30:12 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mutex *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	get_bool(t_mutex *mutex, bool *dest)
{
	bool	result;

	safe_mutex_handle(mutex, LOCK);
	result = *dest;
	safe_mutex_handle(mutex, UNLOCK);
	return (result);
}

void	set_long(t_mutex *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

long	get_long(t_mutex *mutex, long *dest)
{
	long	result;

	safe_mutex_handle(mutex, LOCK);
	result = *dest;
	safe_mutex_handle(mutex, UNLOCK);
	return (result);
}
