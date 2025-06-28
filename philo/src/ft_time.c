/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdaniel- <tdaniel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:14:03 by tdaniel-          #+#    #+#             */
/*   Updated: 2025/06/28 01:32:59 by tdaniel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
infinite loop until it gets to the time
fixed the 1ms constant truncation
*/
void	ft_usleep(long msec)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < msec)
		usleep(10);
}

long	get_time_ms(void)
{
	struct timeval	t;
	long			millisecond;

	if (gettimeofday(&t, NULL) == -1)
	{
		write(2, "\x1b[31mError: gettimeofday failed\n\x1b[0m", 36);
		return (-1);
	}
	millisecond = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (millisecond);
}

long	time_diff(long time)
{
	long	milisecond_diff;

	milisecond_diff = get_time_ms() - time;
	return (milisecond_diff);
}
