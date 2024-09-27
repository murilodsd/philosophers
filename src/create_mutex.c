/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 07:31:24 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/26 05:06:03 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/** 
 * Falta fazer a checagem ainda.
*/
void	create_all_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->n_of_philos)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo->print_mutex, NULL);
	philo->print_mutex_initialized = TRUE;
}