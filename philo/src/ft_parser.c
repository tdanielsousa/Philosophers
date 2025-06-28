/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdaniel- <tdaniel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:14:03 by tdaniel-         #+#    #+#             */
/*   Updated: 2025/06/17 09:19:40 by tdaniel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	argument_parser(char *str)
{
	long	nr;
	int		i;

	nr = 0;
	i = 0;
	if (is_only_numbers(str) == false)
	{
		return (-1);
	}
	while (str[i] != '\0')
	{
		nr = nr * 10 + (str[i] - '0');
		if (nr > INT_MAX)
			return (-1);
		i++;
	}
	return (nr);
}

bool	is_only_numbers(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	are_args_correct(t_simulation **sim)
{
	if (((*sim)->nr_philos < 1) || ((*sim)->nr_philos > 200)
		|| ((*sim)->time_death <= 0) || ((*sim)->time_eat <= 0)
		|| ((*sim)->time_sleep <= 0) || ((*sim)->time_death < 60))
	{
		return (false);
	}
	return (true);
}
