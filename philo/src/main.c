/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdaniel- <tdaniel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:14:03 by tdaniel-          #+#    #+#             */
/*   Updated: 2025/06/20 23:47:10 by tdaniel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo			*philos;
	t_simulation	*sim;

	philos = NULL;
	sim = NULL;
	if ((argc != 5) && (argc != 6))
	{
		write(2, "\x1b[0;31mError: Wrong number of arguments\n\x1b[0m", 44);
		return (1);
	}
	if (initialize(&philos, &sim, argc, argv) != true)
	{
		cleanup(philos, sim);
		return (1);
	}
	if (run_simulation(philos) != true)
	{
		cleanup(philos, sim);
		return (1);
	}
	cleanup(philos, sim);
	return (0);
}
