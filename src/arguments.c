/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:19:09 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/16 16:33:18 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	is_positive_atoi_param_max_10_digits(const char *nptr)
{
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+')
		nptr++;
	if (ft_strlen(nptr) == 1 && *nptr == '0')
		return (FALSE);
	if (ft_strlen(nptr) > 10)
		return (FALSE);
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
	if (!is_positive_atoi_param_max_10_digits(argv[1])
		|| !is_positive_atoi_param_max_10_digits(argv[2])
		|| !is_positive_atoi_param_max_10_digits(argv[3])
		|| !is_positive_atoi_param_max_10_digits(argv[4])
		|| (argc == 6 && !is_positive_atoi_param_max_10_digits(argv[5])))
	{
		ft_printf(2, "Error: All arguments must be a positive number and max of 10 digits\n");
		exit(EXIT_FAILURE);
	}
}

static void	init_pointers(t_philo **philo)
{
	int	n_of_philos;
	t_list	*ptr_list;

	ptr_list = (*philo)->mem_alloc.ptr_mem_list;
	n_of_philos = (*philo)->n_of_philos;
	(*philo)->forks = ft_calloc(n_of_philos, sizeof(pthread_mutex_t));
	check_mem_alloc((*philo), &ptr_list, (*philo)->forks, \
		"ft_calloc failed");
	(*philo)->time_started_to_eat = ft_calloc(n_of_philos, sizeof(long long));
	check_mem_alloc((*philo), &ptr_list, (*philo)->time_started_to_eat, \
		"ft_calloc failed");
	(*philo)->is_philo_enough_fed = ft_calloc(n_of_philos, sizeof(bool));
	check_mem_alloc((*philo), &ptr_list, (*philo)->is_philo_enough_fed, \
		"ft_calloc failed");
	(*philo)->threads = ft_calloc(n_of_philos, sizeof(pthread_t));
	check_mem_alloc((*philo), &ptr_list, (*philo)->threads, \
		"ft_calloc failed");
}

void	get_arguments_and_init(int argc, char *argv[], t_philo **philo)
{	
	errno = 0;
	(*philo)->n_of_philos = ft_atoi(argv[1]);
	(*philo)->time_to_die = ft_atoi(argv[2]);
	(*philo)->time_to_eat = ft_atoi(argv[3]);
	(*philo)->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*philo)->n_of_times_to_eat = ft_atoi(argv[5]);
	else
		(*philo)->n_of_times_to_eat = -1;
	(*philo)->is_over = FALSE;
	(*philo)->is_anyone_dead = FALSE;
	(*philo)->is_all_philos_created = FALSE;
	(*philo)->started_time = get_time();
	(*philo)->forks = NULL;
	(*philo)->threads = NULL;
	(*philo)->print_mutex_initialized = FALSE;
	(*philo)->time_started_to_eat_initialized = FALSE;
	(*philo)->is_over_mutex_initialized = FALSE;
	(*philo)->is_anyone_dead_mutex_initialized = FALSE;
	(*philo)->is_all_philos_created_mutex_initialized = FALSE;
	(*philo)->is_philo_enough_fed_mutex_initialized = FALSE;
	init_pointers(philo);
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
