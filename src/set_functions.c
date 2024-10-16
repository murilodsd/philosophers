/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:24:02 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/16 17:50:08 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_time_philo_started_to_eat(t_threads_params *threads_params)
{
	long long	*time_started_to_eat;

	time_started_to_eat = threads_params->philo->time_started_to_eat;
	time_started_to_eat[threads_params->number - 1] = get_time();
}

void	set_philo_enough_fed_true(t_threads_params *threads_params)
{
	t_philo *philo;

	philo = threads_params->philo;
	safe_set_bool(&philo->is_philo_enough_fed_mutex, \
		&philo->is_philo_enough_fed[threads_params->number - 1], TRUE);
}

void	set_is_over(t_philo *philo, bool value)
{
	safe_set_bool(&philo->is_over_mutex, &philo->is_over, value);
}