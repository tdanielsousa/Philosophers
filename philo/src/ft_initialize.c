/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdaniel- <tdaniel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:14:03 by tdaniel-          #+#    #+#             */
/*   Updated: 2025/06/28 01:57:46 by tdaniel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	initialize(t_philo **philo, t_simulation **sim, int argc, char *argv[])
{
	(*sim) = malloc(sizeof(t_simulation));
	if ((*sim) == NULL)
	{
		write(2, "\x1b[1;31mError: Failed alloc of sim\n\x1b[0m", 38);
		return (false);
	}
	(*sim)->philos_thread_id = NULL;
	if (initialize_parse(sim, argc, argv) == false)
		return (false);
	if (mutex_starter(*sim) == false)
		return (false);
	(*philo) = malloc(sizeof(t_philo) * (*sim)->nr_philos);
	if (*philo == NULL)
	{
		write(2, "\x1b[1;31mError: failure to alloc philos\n\x1b[0m", 43);
		return (false);
	}
	if (initialize_philos(philo, *sim) == false)
	{
		write(2, "\x1b[1;31mError: Failure to init philos\n\x1b[0m", 42);
		return (false);
	}
	return (true);
}

bool	initialize_parse(t_simulation **sim, int ac, char **argv)
{
	(*sim)->nr_philos = argument_parser(argv[1]);
	(*sim)->time_death = argument_parser(argv[2]);
	(*sim)->time_eat = argument_parser(argv[3]);
	(*sim)->time_sleep = argument_parser(argv[4]);
	(*sim)->start_time = get_time_ms();
	(*sim)->time_think = 0;
	(*sim)->all_meals_eaten = false;
	(*sim)->someone_died = false;
	(*sim)->nr_meals = 0;
	if (are_args_correct(sim) == false)
	{
		write(2, "\x1b[1;31mError: Invalid Arguments\n\x1b[0m", 36);
		return (false);
	}
	if (ac == 6)
	{
		(*sim)->nr_meals = argument_parser(argv[5]);
		if ((*sim)->nr_meals <= -1)
		{
			write(2, "\x1b[1;31mError: Invalid Num_Meals\n\x1b[0m", 36);
			return (false);
		}
	}
	return (true);
}

bool	mutex_starter(t_simulation *sim)
{
	if (pthread_mutex_init(&sim->printf_mutex, NULL) != 0)
	{
		write(2, "\x1b[1;31mError: Fail printf mutex\n\x1b[0m", 36);
		return (false);
	}
	if (pthread_mutex_init(&sim->meals_mutex, NULL) != 0)
	{
		write(2, "\x1b[1;31mError: Fail meals mutex\n\x1b[0m", 35);
		return (false);
	}
	if (pthread_mutex_init(&sim->all_meals_eaten_mutex, NULL) != 0)
	{
		write(2, "\x1b[1;31mError: Fail all meals mutex\n\x1b[0m", 39);
		return (false);
	}
	if (pthread_mutex_init(&sim->dead_mutex, NULL) != 0)
	{
		write(2, "\x1b[1;31mError: Fail dead mutex\n\x1b[0m", 34);
		return (false);
	}
	return (true);
}

/*
give all pointers to shared fork array and the sim struct pointer
fill each philo struct with data, circular fork atribuited
if without else for performance, 1 gets fork of last philo
*/
bool	initialize_philos(t_philo **philo, t_simulation *sim)
{
	pthread_mutex_t	*fork;
	int				i;

	fork = fork_initializer(sim->nr_philos);
	if (fork == NULL)
		return (false);
	i = 0;
	while (i < sim->nr_philos)
	{
		(*philo)[i].id = (i + 1);
		(*philo)[i].last_meal_time = sim->start_time;
		(*philo)[i].meals_eaten = 0;
		(*philo)[i].forks_array = fork;
		(*philo)[i].sim = sim;
		(*philo)[i].left_fork = i;
		(*philo)[i].right_fork = (i - 1);
		if ((*philo)[i].id == 1)
			(*philo)[i].right_fork = (sim->nr_philos - 1);
		i++;
	}
	return (true);
}

pthread_mutex_t	*fork_initializer(int nr_philos)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * nr_philos);
	if (!forks)
	{
		write(2, "\x1b[1;31mError: Fail alloc forks\n\x1b[0m", 35);
		return (NULL);
	}
	while (i < nr_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}
