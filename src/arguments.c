/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:19:09 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/23 20:55:26 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	is_positive_atoi_param(const char *nptr)
{
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+')
		nptr++;
	return (ft_isalldigits((char *)nptr));
}

void	check_arguments(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		ft_printf(2, "Error: You should call the philo like that\n\
./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n\
number_of_times_each_philosopher_must_eat is optional");
		exit(EXIT_FAILURE);
	}
	if (!is_positive_atoi_param(argv[1])
		|| !is_positive_atoi_param(argv[2])
		|| !is_positive_atoi_param(argv[3])
		|| !is_positive_atoi_param(argv[4])
		|| !is_positive_atoi_param(argv[5]))
	{
		ft_printf(2, "Error: All arguments must be a positive number\n");
		exit(EXIT_FAILURE);
	}
}

void	get_arguments_and_init(int argc, char *argv[], t_philo **philo)
{	
	int	n_of_philos;
	int	i;
	
	check_arguments(argc, argv);
	n_of_philos = ft_atoi(argv[1]);
	(*philo) = ft_calloc(n_of_philos, sizeof(t_philo));
	//checar
	(*philo)->forks = ft_calloc(n_of_philos, sizeof(pthread_mutex_t));
	//checar
	(*philo)->threads = ft_calloc(n_of_philos, sizeof(pthread_t));
	//checar
	i = 0;
	while (i < n_of_philos)
	{
		(*philo)[i].n_of_philos = n_of_philos;
		(*philo)[i].time_to_die = ft_atoi(argv[2]);
		(*philo)[i].time_to_eat = ft_atoi(argv[3]);
		(*philo)[i].time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			(*philo)[i].n_of_times_to_eat = ft_atoi(argv[5]);
		(*philo)[i].is_over = FALSE;
		(*philo)[i].is_anyone_dead = FALSE;
		(*philo)[i].forks = (*philo)->forks;
		(*philo)[i].threads = (*philo)->threads;
		i++;
	}
}

/* int	main(int argc, char *argv[])
{
	t_philo	philo;

	get_arguments_and_init(argc, argv, &philo);
	ft_printf(1, "Numero de philosofos: %d\n", philo.n_of_philos);
	ft_printf(1, "tempo para morrer: %d\n", philo.time_to_die);
	ft_printf(1, "tempo para comer: %d\n", philo.time_to_eat);
	ft_printf(1, "tempo para dormir: %d\n", philo.time_to_sleep);
	if (argc == 6)
		ft_printf(1, "nº de vezes que cada filosofo deve comer: %d\n", \
			philo.n_of_times_to_eat);
	return (0);
} */
