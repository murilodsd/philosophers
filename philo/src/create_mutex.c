/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 07:31:24 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/22 16:39:57 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/** 
 * TODO checagem
*/

static void	initialize_mutex(t_philo *philo, pthread_mutex_t *mutex, \
	bool *is_initialized)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		destroy_free_exit_error(philo, "pthread_mutex_init failed");
	else
		*is_initialized = TRUE;
}

void	create_all_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->n_of_philos)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		philo->forks_mutex_initialized[i] = TRUE;
		pthread_mutex_init(&philo->time_started_to_eat_mutex[i], NULL);
		philo->time_started_to_eat_initialized[i] = TRUE;
		pthread_mutex_init(&philo->is_philo_enough_fed_mutex[i], NULL);
		philo->is_philo_enough_fed_mutex_initialized[i] = TRUE;
		i++;
	}
	initialize_mutex(philo, &philo->print_mutex, \
		&philo->print_mutex_initialized);
	initialize_mutex(philo, &philo->is_over_mutex, \
		&philo->is_over_mutex_initialized);
	initialize_mutex(philo, &philo->is_anyone_dead_mutex, \
		&philo->is_anyone_dead_mutex_initialized);
	initialize_mutex(philo, &philo->is_all_philos_created_mutex, \
		&philo->is_all_philos_created_mutex_initialized);
}
