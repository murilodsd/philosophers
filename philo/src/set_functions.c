/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:24:02 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/22 16:38:51 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_time_philo_started_to_eat(t_philo *philo, int philo_nbr, \
	long long value)
{
	long long	*time_started_to_eat;

	time_started_to_eat = philo->time_started_to_eat;
	safe_set_long_long(&philo->time_started_to_eat_mutex[philo_nbr - 1], \
		&time_started_to_eat[philo_nbr - 1], value);
}

void	set_philo_enough_fed_true(t_threads_params *threads_params)
{
	t_philo	*philo;

	philo = threads_params->philo;
	safe_set_bool(&philo->is_philo_enough_fed_mutex[threads_params->number - 1], \
		&philo->is_philo_enough_fed[threads_params->number - 1], TRUE);
}

void	set_is_over(t_philo *philo, bool value)
{
	safe_set_bool(&philo->is_over_mutex, &philo->is_over, value);
}

void	set_all_threads_created(t_philo *philo)
{
	safe_set_bool(&philo->is_all_philos_created_mutex, \
		&philo->is_all_philos_created, TRUE);
}
