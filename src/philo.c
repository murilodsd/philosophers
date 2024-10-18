/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:07:32 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/18 13:36:23 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	wait_philo_die_or_philos_fed(t_philo *philo)
{
	int		i;

	while (!check_philo_is_dead(philo) && !check_all_philos_fed(philo))
		;
	i = 0;
	while (i < philo->n_of_philos)
		pthread_join(philo->threads[i++], NULL);
}

int	main(int argc, char *argv[])
{
	t_philo	*philo;

	check_arguments(argc, argv);
	philo = ft_calloc(1, sizeof(t_philo));
	if (!philo)
	{
		ft_printf(2, "ft_calloc failed");
		exit(EXIT_FAILURE);
	}
	get_arguments_and_init(argc, argv, &philo);
	create_all_mutex(philo);
	create_all_philos(philo);
	wait_philo_die_or_philos_fed(philo);
	destroy_all_mutex(philo);
	free_all(philo);
	return (0);
}
