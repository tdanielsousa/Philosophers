/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdaniel- <tdaniel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:14:03 by tdaniel-          #+#    #+#             */
/*   Updated: 2025/06/28 01:38:18 by tdaniel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_philo *philo, t_simulation *sim)
{
	if (sim != NULL)
	{
		free(sim);
	}
	if (philo != NULL && philo->forks_array != NULL)
	{
		free(philo->forks_array);
	}
	if (philo != NULL)
	{
		free(philo);
	}
}

void	destroy_mutexes(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->sim->nr_philos)
	{
		pthread_mutex_destroy(&philo->forks_array[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->sim->printf_mutex);
	pthread_mutex_destroy(&philo->sim->meals_mutex);
	pthread_mutex_destroy(&philo->sim->all_meals_eaten_mutex);
	pthread_mutex_destroy(&philo->sim->dead_mutex);
}

void	print_msg(t_philo *p, char *str)
{
	pthread_mutex_lock(&p->sim->printf_mutex);
	if ((is_any_dead(p) == false) && (is_all_meals_eaten(p) == false))
	{
		printf("%3ld %3d %s\n", (time_diff(p->sim->start_time)), p->id, str);
	}
	pthread_mutex_unlock(&p->sim->printf_mutex);
}

bool	is_nrphilo_even(int n)
{
	if (n % 2 == 0)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}
