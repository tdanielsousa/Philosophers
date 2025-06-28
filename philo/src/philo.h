/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdaniel- <tdaniel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:14:03 by tdaniel-          #+#    #+#             */
/*   Updated: 2025/06/28 02:04:05 by tdaniel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ****************************** Headers ********************************* */
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* ****************************** Structures ****************************** */
/* Simulation struct gets all mutexes and "general" vars
printf_mutex 			-> mutex for printf
meals_mutex 			-> mutex for meals
dead_mutex 				-> mutex for is dead
all_meals_eaten_mutex 	->  mutex for all eaten
time_death 				-> time till death ms
time_eat				-> time to eat ms
time_sleep 				-> time to sleep ms
time_think 				-> time to think ms
start_time 				-> Start time of the simulation, ms
philos_thread_id is a pointer to an array of pthread_t
So philos_thread_id[i] holds the thread ID of the i'eth philosopher thread.
Array of structs VS struct of arrays
Array of structs */
typedef struct s_simulation
{
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	all_meals_eaten_mutex;

	pthread_t		*philos_thread_id;

	int				nr_philos;
	int				nr_meals;

	long			time_death;
	long			time_eat;
	long			time_sleep;
	long			time_think;

	long			start_time;

	bool			all_meals_eaten;
	bool			someone_died;

}					t_simulation;

/* ************************************************************************ */
/* Philo[i] struct
id 				->	philo's id
last_meal_time 	-> last time philo[i] ate
meals_eaten  	-> Number of meals eaten by each philo[i]
left_fork 		-> philo[i] left fork
right_fork 		-> philo[i]right fork
sim 			-> to acess sim struct
forks_array 	-> Pointer to an Array of forks
Changed to pointer to array so they can all share the same array */
typedef struct s_philo
{
	int				id;

	long			last_meal_time;
	int				meals_eaten;

	int				left_fork;
	int				right_fork;

	t_simulation	*sim;

	pthread_mutex_t	*forks_array;

}					t_philo;

/* ************************** Prototypes ********************************** */
/* ******** ft_utils.c ******** */
void				cleanup(t_philo *philo, t_simulation *sim);
void				destroy_mutexes(t_philo *philo);
void				print_msg(t_philo *p, char *str);
bool				is_nrphilo_even(int n);
/* ******** ft_time.c ******** */
void				ft_usleep(long msec);
long				get_time_ms(void);
long				time_diff(long time);
/* ******** ft_simulation.c ******** */
void				*start_philosopher_routine(void *args);
bool				join_philosopher_threads(t_philo *philos);
bool				create_philosopher_threads(t_philo *philos);
bool				run_simulation(t_philo *philos);
void				delay_beginning(t_philo *philo);
/* ******** ft_parser.c ******** */
bool				are_args_correct(t_simulation **sim);
long				argument_parser(char *str);
bool				is_only_numbers(char *str);
/* ******** ft_mutexes.c ******** */
void				set_all_meals_eaten(t_simulation *sim);
bool				is_all_meals_eaten(t_philo *philo);
bool				check_all_meals_done(t_philo *philo, t_simulation *sim);
void				set_someone_die(t_simulation *sim);
bool				is_any_dead(t_philo *philo);
/* ******** ft_initialize.c ******** */
bool				initialize_parse(t_simulation **sim, int ac, char **argv);
bool				mutex_starter(t_simulation *sim);
bool				initialize_philos(t_philo **philo, t_simulation *sim);
pthread_mutex_t		*fork_initializer(int nr_philos);
bool				initialize(t_philo **philo, t_simulation **sim, int argc,
						char *argv[]);
/* ******** ft_eat.c ******** */
bool				acquire_forks(t_philo *p);
void				release_forks(t_philo *p);
bool				attempt_eat(t_philo *p);
void				monitor_simulation(t_philo *philo, t_simulation *sim);

#endif
