/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:43:01 by jgamarra          #+#    #+#             */
/*   Updated: 2024/12/06 22:48:16 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_custom_atoi(char *str)
{
	long	number;
	size_t	index;

	number = 0;
	index = 0;
	while (str[index] && (str[index] == ' ' || str[index] == '\t'
			|| str[index] == '\n' || str[index] == '\r'
			|| str[index] == 'f' || str[index] == 'v'))
		index++;
	if (str[index] == '+')
		index++;
	else if (str[index] == '-')
		return (-1);
	while (str[index] != '\0')
	{
		if (str[index] >= '0' && str[index] <= '9')
			number = (number * 10) + (str[index] - '0');
		else
			return (-1);
		index++;
	}
	if (number > INT_MAX)
		return (-1);
	return (number);
}

int	ft_return_message(char *str, int code)
{
	printf("%s", str);
	return (code);
}

int	valid_args(t_table *table, int argc)
{
	if ((table->philo_number == -1 || table->philo_number == 0)
		|| table->time_to_die == (-1 * 1e3)
		|| table->time_to_eat == (-1 * 1e3)
		|| table->time_to_sleep == (-1 * 1e3))
		return (ft_return_message("Error: Number not valid.\n", 1));
	if (argc == 6)
	{
		if (table->limit_meals == -1)
			return (ft_return_message("Error: Number not valid.\n", 1));
	}
	return (0);
}

void	set_initial(t_table *table)
{
	table->philo_number = -1;
	table->time_to_die = -1;
	table->time_to_eat = -1;
	table->time_to_sleep = -1;
	table->limit_meals = -1;
}

int	process_initial_args(int argc, char **argv, t_table *table)
{
	set_initial(table);
	if (argc > 6)
		return (ft_return_message("Error: Too many arguments.\n", 1));
	if (argc >= 5)
	{
		printf("Initial Params:\n");
		printf("Number of philosophers: %s\n", argv[1]);
		printf("Time to die: %s\n", argv[2]);
		printf("Time to eat: %s\n", argv[3]);
		printf("Time to sleep: %s\n", argv[4]);
		table->philo_number = ft_custom_atoi(argv[1]);
		table->time_to_die = ft_custom_atoi(argv[2]) * 1e3;
		table->time_to_eat = ft_custom_atoi(argv[3]) * 1e3;
		table->time_to_sleep = ft_custom_atoi(argv[4]) * 1e3;
		if (argc == 6)
		{
			printf("Number of times each philosopher must eat: %s\n", argv[5]);
			table->limit_meals = ft_custom_atoi(argv[5]);
		}
	}
	if (argc < 5 || argc > 6)
		return (ft_return_message("Error: Arguments not valid.\n", 1));
	return (valid_args(table, argc));
}
