/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutexes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdaniel- <tdaniel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:14:03 by tdaniel-          #+#    #+#             */
/*   Updated: 2025/06/28 02:25:24 by tdaniel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_any_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->dead_mutex);
	if (philo->sim->someone_died == true)
	{
		pthread_mutex_unlock(&philo->sim->dead_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->sim->dead_mutex);
	return (false);
}

void	set_someone_die(t_simulation *sim)
{
	pthread_mutex_lock(&sim->dead_mutex);
	sim->someone_died = true;
	pthread_mutex_unlock(&sim->dead_mutex);
}

bool	check_all_meals_done(t_philo *philo, t_simulation *sim)
{
	int	i;
	int	philo_finished_count;
	int	meals_count;

	philo_finished_count = 0;
	i = 0;
	while (i < sim->nr_philos)
	{
		pthread_mutex_lock(&philo->sim->meals_mutex);
		meals_count = philo[i].meals_eaten;
		pthread_mutex_unlock(&philo->sim->meals_mutex);
		if (meals_count >= sim->nr_meals)
			philo_finished_count++;
		i++;
	}
	if (philo_finished_count == sim->nr_philos)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

bool	is_all_meals_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->all_meals_eaten_mutex);
	if (philo->sim->all_meals_eaten == true)
	{
		pthread_mutex_unlock(&philo->sim->all_meals_eaten_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->sim->all_meals_eaten_mutex);
	return (false);
}

void	set_all_meals_eaten(t_simulation *sim)
{
	pthread_mutex_lock(&sim->all_meals_eaten_mutex);
	sim->all_meals_eaten = true;
	pthread_mutex_unlock(&sim->all_meals_eaten_mutex);
}
