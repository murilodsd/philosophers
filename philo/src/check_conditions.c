/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_conditions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:19:23 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/18 13:36:36 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	check_philo_is_dead(t_philo *philo)
{
	int			i;
	long long	time_without_eating;
	long long	time_now;

	i = 0;
	while (i < philo->n_of_philos)
	{
		time_now = get_time();
		time_without_eating = time_now - get_time_started_to_eat(philo, i);
		if (time_without_eating >= philo->time_to_die)
		{
			set_is_over(philo, TRUE);
			print_death(philo, i + 1);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void	check_i_am_enough_fed(t_threads_params *threads_params)
{
	t_philo	*philo;

	philo = threads_params->philo;
	check_program_is_over(philo);
	if (threads_params->eat_count == philo->n_of_times_to_eat)
		set_philo_enough_fed_true(threads_params);
}

bool	check_all_philos_fed(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->n_of_philos)
	{
		if (!get_is_philo_enough_fed(philo, i))
			return (FALSE);
		i++;
	}
	set_is_over(philo, TRUE);
	return (TRUE);
}

void	check_program_is_over(t_philo *philo)
{
	if (get_is_over(philo))
		pthread_exit(NULL);
}
