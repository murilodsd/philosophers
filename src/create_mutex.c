/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 07:31:24 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/12 12:44:17 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/** 
 * Falta fazer a checagem ainda.
*/

static void	initialize_mutex(t_philo *philo, pthread_mutex_t *mutex, bool *is_initialized)
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
		i++;
	}
	initialize_mutex(philo, &philo->print_mutex, &philo->print_mutex_initialized);
	initialize_mutex(philo, &philo->is_over_mutex, &philo->is_over_mutex_initialized);
	initialize_mutex(philo, &philo->is_anyone_dead_mutex, &philo->is_anyone_dead_mutex_initialized);
	initialize_mutex(philo, &philo->is_all_philos_created_mutex, &philo->is_all_philos_created_mutex_initialized);
	initialize_mutex(philo, &philo->is_philo_enough_fed_mutex, &philo->is_philo_enough_fed_mutex_initialized);
}