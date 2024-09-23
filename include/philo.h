/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:03:02 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/23 20:56:07 by mde-souz         ###   ########.fr       */
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
	int					n_of_philos;
	int					time_to_die;
	int	 				time_to_eat;
	int					time_to_sleep;
	int					n_of_times_to_eat;
	bool				*is_over;
	int	number;
	bool	*is_anyone_dead;	
	pthread_t	*threads;
	pthread_mutex_t	*forks;
}	t_philo;

void	create_all_mutex(t_philo *philo);
void	get_arguments_and_init(int argc, char *argv[], t_philo **philo);
#endif