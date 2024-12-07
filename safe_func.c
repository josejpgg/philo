/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:29:56 by jgamarra          #+#    #+#             */
/*   Updated: 2024/12/06 18:48:39 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (!result)
		printf("Error: malloc failed\n");
	return (result);
}

static void	handle_mutex_error(int status, t_action action)
{
	if (0 == status)
		return ;
	if (EINVAL == status
		&& (LOCK == action || UNLOCK == action || DESTROY == action))
		printf("Error: The value specified by mutex is invalid\n");
	else if (EINVAL == status && (INIT == action))
		printf("Error: The value specified by attr is invalid\n");
	else if (EDEADLK == status)
		printf("Error: A dLock is possible for thread blocked waiting mutex\n");
	else if (EPERM == status)
		printf("Error: The current thread does not hold a lock on mutex\n");
	else if (ENOMEM == status)
		printf("Error: The processo cannot allocate enough memory for mutex\n");
	else if (EBUSY == status)
		printf("Mutex is locked\n");
}

void	safe_mutex_handle(t_mutex *mutex, t_action action)
{
	if (action == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), action);
	else if (action == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), action);
	else if (action == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), action);
	else if (action == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), action);
	else
		printf("Error: invalid action for mutex handle\n");
}

static void	handle_thread_error(int status, t_action action)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		printf("Error: No resources to create another thread\n");
	else if (EPERM == status)
		printf("Error: The caller does not have appropiate permission\n");
	else if (EINVAL == status && CREATE == action)
		printf("Error: The value specified by attr is invalid\n");
	else if (EINVAL == status && (JOIN == action || DETACH == action))
		printf("Error: The value specified by thread is not joinable\n");
	else if (ESRCH == status)
		printf("Error: No thread could be found by the given thread ID\n");
	else if (EDEADLK == status)
		printf("Error: A deadlock was detected\n");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
	void *data, t_action action)
{
	if (CREATE == action)
		handle_thread_error(pthread_create(thread, NULL, foo, data), action);
	else if (JOIN == action)
		handle_thread_error(pthread_join(*thread, NULL), action);
	else if (DETACH == action)
		handle_thread_error(pthread_detach(*thread), action);
	else
		printf("Error: invalid action for thread handle\n");
}
