/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdaniel- <tdaniel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:14:03 by tdaniel-          #+#    #+#             */
/*   Updated: 2025/06/28 02:22:04 by tdaniel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	run_simulation(t_philo *philos)
{
	if (create_philosopher_threads(philos) == false)
	{
		return (false);
	}
	monitor_simulation(philos, philos->sim);
	if (join_philosopher_threads(philos) == false)
	{
		return (false);
	}
	destroy_mutexes(philos);
	free(philos->sim->philos_thread_id);
	return (true);
}

bool	create_philosopher_threads(t_philo *philos)
{
	int	i;

	i = 0;
	philos->sim->philos_thread_id = malloc(sizeof(pthread_t)
			* philos->sim->nr_philos);
	if (philos->sim->philos_thread_id == NULL)
		return (false);
	while (i < philos->sim->nr_philos)
	{
		if (pthread_create(&philos->sim->philos_thread_id[i], NULL,
				start_philosopher_routine, &philos[i]))
		{
			while (i > 0)
			{
				i--;
				pthread_join(philos->sim->philos_thread_id[i], NULL);
			}
			free(philos->sim->philos_thread_id);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	join_philosopher_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->sim->nr_philos)
	{
		if (pthread_join(philos->sim->philos_thread_id[i], NULL))
			return (false);
		i++;
	}
	return (true);
}

void	delay_beginning(t_philo *philo)
{
	if (is_nrphilo_even(philo->sim->nr_philos) == true)
	{
		if (philo->id % 2 == 0)
		{
			print_msg(philo, "\x1b[1;36mis thinking\x1b[0m");
			ft_usleep(philo->sim->time_eat);
		}
	}
	else
	{
		if (philo->id % 2 == 1 && philo->id != philo->sim->nr_philos)
		{
			print_msg(philo, "\x1b[1;36mis thinking\x1b[0m");
		}
		else if (philo->id % 2 == 0)
		{
			print_msg(philo, "\x1b[1;36mis thinking\x1b[0m");
			ft_usleep(philo->sim->time_eat);
		}
		else if (philo->id == philo->sim->nr_philos && philo->id % 2 == 1)
		{
			print_msg(philo, "\x1b[1;36mis thinking\x1b[0m");
			ft_usleep(philo->sim->time_eat * 2);
		}
	}
}

void	*start_philosopher_routine(void *ref)
{
	t_philo	*philo;

	philo = (t_philo *)ref;
	delay_beginning(philo);
	while (1)
	{
		if (is_any_dead(philo) == true)
			break ;
		if (attempt_eat(philo) != true)
			break ;
		print_msg(philo, "\x1b[1;36mis thinking\x1b[0m");
		ft_usleep(philo->sim->time_think);
	}
	return (NULL);
}
