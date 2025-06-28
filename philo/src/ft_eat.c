/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdaniel- <tdaniel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:14:03 by tdaniel-          #+#    #+#             */
/*   Updated: 2025/06/28 02:57:31 by tdaniel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
debug after set all meals
printf("%3ld %3d all have eaten!\n", time_diff(philo[i].sim->start_time),
	philo[i].id);
	add the 3 min width to align ouput
*/
void	monitor_simulation(t_philo *philo, t_simulation *sim)
{
	long	l_meal;
	int		i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->sim->meals_mutex);
		l_meal = philo[i].last_meal_time;
		pthread_mutex_unlock(&philo->sim->meals_mutex);
		if (sim->nr_meals > 0 && (check_all_meals_done(philo, sim) == true))
		{
			set_all_meals_eaten(sim);
			break ;
		}
		if (l_meal && ((get_time_ms() - l_meal) > sim->time_death))
		{
			set_someone_die(sim);
			printf("%3ld %3d \x1b[1;31mdied\x1b[0m\n",
				time_diff(philo[i].sim->start_time), philo[i].id);
			break ;
		}
		i = ((i + 1) % sim->nr_philos);
		usleep(20);
	}
}

bool	attempt_eat(t_philo *p)
{
	if (acquire_forks(p) != true)
	{
		return (false);
	}
	pthread_mutex_lock(&p->sim->meals_mutex);
	p->last_meal_time = get_time_ms();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->sim->meals_mutex);
	if (is_any_dead(p) == true || is_all_meals_eaten(p) == true)
	{
		release_forks(p);
		return (false);
	}
	ft_usleep(p->sim->time_eat);
	release_forks(p);
	return (true);
}

/*
if (first == second) // only 1 philo
added if (p->left_fork < p->right_fork) because of helgrind
always picking the lower numbered fork first to avoids deadlock
*/
bool	acquire_forks(t_philo *p)
{
	int	first;
	int	second;

	if (p->left_fork < p->right_fork)
	{
		first = p->left_fork;
		second = p->right_fork;
	}
	else
	{
		first = p->right_fork;
		second = p->left_fork;
	}
	pthread_mutex_lock(&p->forks_array[first]);
	print_msg(p, "\x1b[1;32mhas taken a fork\x1b[0m");
	if (first == second)
	{
		pthread_mutex_unlock(&p->forks_array[first]);
		return (false);
	}
	pthread_mutex_lock(&p->forks_array[second]);
	print_msg(p, "\x1b[1;32mhas taken a fork\x1b[0m");
	print_msg(p, "\x1b[1;35mis eating\x1b[0m");
	return (true);
}

/*
debug forks
print_msg(p, "\x1b[0;33mhas drop a fork\x1b[0m");
*/
void	release_forks(t_philo *p)
{
	int	first;
	int	second;

	first = p->left_fork;
	second = p->right_fork;
	pthread_mutex_unlock(&p->forks_array[first]);
	pthread_mutex_unlock(&p->forks_array[second]);
	print_msg(p, "\x1b[1;33mis sleeping\x1b[0m");
	if (is_nrphilo_even(p->sim->nr_philos) == true)
	{
		ft_usleep(p->sim->time_sleep);
	}
	else
	{
		ft_usleep(p->sim->time_sleep + p->sim->time_eat);
	}
}
