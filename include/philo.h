/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:03:02 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/15 19:41:49 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "../lib/libft/include/libft.h"

/**
 * n_of_philos: The number of philosophers and also the number of forks.
 * time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
 * milliseconds since the beginning of their last meal or
 * the beginning of the simulation, they die.
 * time_to_eat (in milliseconds): The time it takes for a philosopher to eat.During that time, they will need to hold two forks.
 * time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
 * number_of_times_each_philosopher_must_eat (optional argument): 
 * If all philosophers have eaten at least number_of_times_each_philosopher_must_eat
 * times, the simulation stops. If not specified, the simulation stops when a
 * philosopher dies
 */
typedef struct s_philo
{
	t_mem_alloc	mem_alloc;
	long long			started_time;
	int					n_of_philos;
	int					time_to_die;
	int	 				time_to_eat;
	int					time_to_sleep;
	int					n_of_times_to_eat;
	long long	*time_started_to_eat;
	bool		*is_philo_enough_fed;
	bool			is_over;
	bool			is_anyone_dead;
	bool			is_all_philos_created;
	pthread_t	*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	time_started_to_eat_mutex;
	pthread_mutex_t	is_over_mutex;
	pthread_mutex_t	is_anyone_dead_mutex;
	pthread_mutex_t	is_all_philos_created_mutex;
	pthread_mutex_t	is_philo_enough_fed_mutex;
	bool                print_mutex_initialized;
	bool                time_started_to_eat_initialized;
	bool                is_over_mutex_initialized;
	bool                is_anyone_dead_mutex_initialized;
	bool                is_all_philos_created_mutex_initialized;
	bool                is_philo_enough_fed_mutex_initialized;
}	t_philo;

typedef struct s_threads_params
{
	t_philo	*philo;
	int	number;
	int	eat_count;
} t_threads_params;

void		check_arguments(int argc, char *argv[]);
void		get_arguments_and_init(int argc, char *argv[], t_philo **philo);
void		create_all_mutex(t_philo *philo);
void		create_all_philos(t_philo *philo);
void		print_action(t_threads_params *threads_params, char *msg, bool is_eating);
void		print_death(t_philo *philo, int philo_number);
void		print_debug(t_philo *philo, char *msg);
long long	get_time(void);
void		ft_msleep(t_philo *philo, long msec);
void		get_forks(t_threads_params *threads_params, pthread_mutex_t *left_fork_mutex, pthread_mutex_t *right_fork_mutex);
void		check_mem_alloc(t_philo *philo, t_list **ptr_or_matrix_list, void *ptr, char *error_msg);
void		start_to_think(t_threads_params *threads_params);
void		start_to_sleep(t_threads_params *threads_params);
void		check_program_is_over(t_philo *philo);
void		save_pointer(t_philo *philo, t_list **ptr_or_matrix_list, void *ptr);
void		destroy_all_mutex(t_philo *philo);
void		free_all(t_philo *philo);
void		destroy_free_exit_error(t_philo *philo, char *error_msg);
void		safe_set_bool(pthread_mutex_t *mutex, bool *variable, bool value);
bool		safe_get_bool(pthread_mutex_t *mutex, bool *variable);
void		safe_set_long_long(pthread_mutex_t *mutex, long long *variable, long long value);
long long	safe_get_long_long(pthread_mutex_t *mutex, long long *variable);
#endif