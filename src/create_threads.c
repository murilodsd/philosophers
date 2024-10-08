/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 05:06:18 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/08 20:37:44 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*pthread_created(void *params)
{
	t_threads_params	*threads_params;
	int	left_fork_index;
	int	right_fork_index;

	threads_params = (t_threads_params *)params;
	//ft_printf(1, "Philo number %d\n", philo->number);
	left_fork_index = threads_params->number - 1;
	if (threads_params->number == 1)
		right_fork_index = threads_params->philo->n_of_philos - 1;
	else
		right_fork_index = threads_params->number - 2;
	//ft_printf(1, "Philo %d created, Garfo da direita %d, Garfo da esquerda %d\n", philo->number, right_fork_index + 1, left_fork_index + 1);
	if (threads_params->number % 2 == 0)
		usleep(200);
	while (1)
	{
		get_forks(threads_params, &threads_params->philo->forks[left_fork_index], &threads_params->philo->forks[right_fork_index]);
		start_to_sleep(threads_params);
		start_to_think(threads_params);
	}
	free(threads_params);
	pthread_exit(NULL);	
}
void	create_philo(t_philo *philo, int index)
{
	t_threads_params *threads_params;

	threads_params = ft_calloc(1, sizeof(t_threads_params));
	threads_params->number = index + 1;
	threads_params->philo = philo;
	//ft_printf(1, "entrou no create philo number %d\n", philo->number);
	pthread_create(&philo->threads[index], NULL, pthread_created, threads_params);	
}


void	create_all_philos(t_philo *philo)
{
	int	i;
	
	i = 0; 
	while(i < philo->n_of_philos)
	{	
		create_philo(philo, i);
		i++;
	}
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
	philo->forks = ft_calloc(philo->n_of_philos, sizeof(pthread_mutex_t));
	check_mem_alloc(philo, &philo->mem_alloc.ptr_mem_list, philo->forks, "ft_calloc failed");
	philo->threads = ft_calloc(philo->n_of_philos, sizeof(pthread_t));
	check_mem_alloc(philo, &philo->mem_alloc.ptr_mem_list, philo->threads, "ft_calloc failed");
	philo->time_started_to_eat = ft_calloc(philo->n_of_philos, sizeof(long));
	check_mem_alloc(philo, &philo->mem_alloc.ptr_mem_list, philo->time_started_to_eat, "ft_calloc failed");
	create_all_mutex(philo);
	ft_printf(1, "Numero de philosofos: %d\n", philo->n_of_philos);
	ft_printf(1, "tempo para morrer: %d\n", philo->time_to_die);
	ft_printf(1, "tempo para comer: %d\n", philo->time_to_eat);
	ft_printf(1, "tempo para dormir: %d\n", philo->time_to_sleep);
	if (argc == 6)
		ft_printf(1, "nº de vezes que cada filosofo deve comer: %d\n", \
			philo->n_of_times_to_eat);
	philo->start_time = get_time();
	create_all_philos(philo);
	destroy_all(philo);
	free_all(philo);
	return (0);
}