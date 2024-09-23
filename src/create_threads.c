/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 05:06:18 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/23 12:43:12 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	create_philo(int philo_number)
{

	
}

void	*pthread_created(void *params)
{
	t_philo	*philo;

	philo = (t_philo *)params;
	ft_printf(1, "Philo %d created\n", philo->number);
	if (philo->number%2)
			
}

void	create_all_philos(t_philo *philo)
{
	int		i;
	t_philo	philos[program->n_of_philos + 1];

	ft_bzero(philos, sizeof(t_philo)*(program->n_of_philos + 1));
	i = 0;
	while(i < program->n_of_philos)
	{	
		philos[i].number = i + 1;
		pthread_create(&philos[i].thread, NULL, pthread_created, &philos[i]);
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_philo	philo;

	get_arguments(argc, argv, &philo);
	ft_printf(1, "Numero de philosofos: %d\n", philo.n_of_philos);
	ft_printf(1, "tempo para morrer: %d\n", philo.time_to_die);
	ft_printf(1, "tempo para comer: %d\n", philo.time_to_eat);
	ft_printf(1, "tempo para dormir: %d\n", philo.time_to_sleep);
	if (argc == 6)
		ft_printf(1, "nº de vezes que cada filosofo deve comer: %d\n", \
			philo.n_of_times_to_eat);
	create_all_philos(&philo);	
	return (0);
}