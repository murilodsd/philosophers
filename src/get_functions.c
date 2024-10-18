/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:49:54 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/18 12:33:08 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	get_is_all_philo_created(t_threads_params *threads_params)
{
	return (safe_get_bool(&threads_params->philo->is_all_philos_created_mutex, \
		&threads_params->philo->is_all_philos_created));
}

long long	get_time_started_to_eat(t_philo *philo, int philo_index)
{
	return (safe_get_long_long(&philo->time_started_to_eat_mutex, \
		&philo->time_started_to_eat[philo_index]));
}

bool	get_is_philo_enough_fed(t_philo *philo, int philo_nbr)
{
	return (safe_get_bool(&philo->is_philo_enough_fed_mutex, \
		&philo->is_philo_enough_fed[philo_nbr]));
}

bool	get_is_over(t_philo *philo)
{
	return (safe_get_bool(&philo->is_over_mutex, \
			&philo->is_over));
}
