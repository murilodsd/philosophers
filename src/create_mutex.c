/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 07:31:24 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/23 13:20:52 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/** 
 * Falta fazer a checagem ainda.
*/
void	create_all_mutex(t_philo *philo)
{
	int	i;

	philo->forks = ft_calloc(philo->n_of_philos, \
		sizeof(pthread_mutex_t *));
	i = 0;
	while (i < philo->n_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}