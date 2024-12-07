/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:30:00 by jgamarra          #+#    #+#             */
/*   Updated: 2024/12/06 21:19:39 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *table_forks, int index)
{
	long	philo_number;

	philo_number = philo->table->philo_number;
	philo->first_fork = &table_forks[(index + 1) % philo_number];
	philo->second_fork = &table_forks[index];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &table_forks[index];
		philo->second_fork = &table_forks[(index + 1) % philo_number];
	}
}

static void	sit_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_number)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->enough_meals = false;
		philo->meals_counter = 0;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		philo->table = table;
		assign_forks(philo, table->forks, i);
	}
}

void	prepare_table(t_table *table)
{
	int	i;

	table->end_simulation = false;
	table->philos_ready = false;
	table->philos_running = 0;
	table->philos = (t_philo *)safe_malloc(
			sizeof(t_philo) * table->philo_number);
	table->forks = (t_fork *)safe_malloc(
			sizeof(t_fork) * table->philo_number);
	safe_mutex_handle(&table->table_mutex, INIT);
	safe_mutex_handle(&table->write_mutex, INIT);
	i = -1;
	while (++i < table->philo_number)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].id = i;
	}
	sit_philos(table);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (process_initial_args(argc, argv, &table) == 1)
		return (1);
	prepare_table(&table);
	dinner_start(&table);
	clean(&table);
	return (0);
}
