/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:07:32 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/16 08:47:43 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_time_started_to_eat(t_philo *philo, int philo_index)
{
	return (safe_get_long_long(&philo->time_started_to_eat_mutex, \
		&philo->time_started_to_eat[philo_index]));
}

void	set_is_over(t_philo *philo, bool value)
{
	safe_set_bool(&philo->is_over_mutex, &philo->is_over, value);
}

bool	check_philo_is_dead(t_philo *philo)
{
	int			i;
	long long	time_without_eating;
	long long	time_now;

	i = 0;
	while(i < philo->n_of_philos)
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

bool	check_all_philos_fed(t_philo *philo)
{
	int	i;

	i = 0;
	while(i < philo->n_of_philos)
	{
		if (safe_get_bool(&philo->is_philo_enough_fed_mutex, &philo->is_philo_enough_fed[i]) == FALSE)
			return (FALSE);
		i++;
	}
	philo->is_over = TRUE;
	return (TRUE);
}

void	wait_philo_die_or_philos_fed(t_philo *philo)
{
	int		i;

	while (!check_philo_is_dead(philo) && !check_all_philos_fed(philo))
		;
	i = 0;
	while(i < philo->n_of_philos)
		pthread_join(philo->threads[i++], NULL);
}

int	main(int argc, char *argv[])
{
	t_philo	*philo;
	int	n_of_philos;

	check_arguments(argc, argv);
	philo = ft_calloc(1, sizeof(t_philo));
	if (!philo)
	{
		ft_printf(2, "ft_calloc failed");
		exit(EXIT_FAILURE);
	}
	get_arguments_and_init(argc, argv, &philo);
	ft_printf(1, "Numero de philosofos: %d\n", philo->n_of_philos);
	ft_printf(1, "tempo para morrer: %d\n", philo->time_to_die);
	ft_printf(1, "tempo para comer: %d\n", philo->time_to_eat);
	ft_printf(1, "tempo para dormir: %d\n", philo->time_to_sleep);
	if (argc == 6)
		ft_printf(1, "nº de vezes que cada filosofo deve comer: %d\n", \
			philo->n_of_times_to_eat);
	create_all_mutex(philo);
	create_all_philos(philo);
	wait_philo_die_or_philos_fed(philo);
	destroy_all_mutex(philo);
	free_all(philo);
	return (0);
}