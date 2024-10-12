/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 05:06:18 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/11 23:20:27 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_if_am_dead_or_program_is_over(t_threads_params *threads_params)
{
	t_philo *philo;
	long long	time_without_eating;

	philo = threads_params->philo;
	if (philo->is_over == TRUE)
		pthread_exit(NULL);
	time_without_eating = get_time() - philo->time_started_to_eat[threads_params->number - 1];
	pthread_mutex_lock(&philo->print_mutex);
/* 	ft_printf(1, GREEN "philo %d\n" RESET, threads_params->number);
	ft_printf(1, GREEN "tempo agora %d\n" RESET, get_time());
	ft_printf(1, GREEN "tempo ultima refeicao %d\n" RESET, philo->time_started_to_eat[threads_params->number - 1]);
	ft_printf(1, GREEN "tempo sem comer %d\n" RESET, time_without_eating); */
	pthread_mutex_unlock(&philo->print_mutex);
	if (time_without_eating >= philo->time_to_die)
	{
		philo->is_anyone_dead = TRUE;
		print_action(threads_params,RED "%d %d is dead\n" RESET, FALSE);
		pthread_exit(NULL);
	}
}

/* void	check_if_any_philo_died(t_threads_params *threads_params)
{
	int	i;
	t_philo *philo;
	long long	time_without_eating;

	philo = threads_params->philo;
	if (philo->is_anyone_dead == TRUE)
		pthread_exit(NULL);
	i = 0;
	while (i < philo->n_of_philos)
	{
		pthread_mutex_lock(&philo->print_mutex);
		ft_printf(1,GREEN "philo %d hora agora %d e quando comecou a comer %d\n" RESET, threads_params->number, get_time(), philo->time_started_to_eat[i]);
		pthread_mutex_unlock(&philo->print_mutex);
		time_without_eating = get_time() - philo->time_started_to_eat[i];
		if (time_without_eating >= philo->time_to_die)
		{
			philo->is_anyone_dead = TRUE;
			print_action(threads_params, "%d %d is dead", FALSE);
			pthread_exit(NULL);
		}
		i++;
	}
} */

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
	while (!threads_params->philo->all_philos_created)
		;
	//ft_printf(1, "Philo %d created, Garfo da direita %d, Garfo da esquerda %d\n", philo->number, right_fork_index + 1, left_fork_index + 1);
	if (threads_params->number % 2 == 0)
		usleep(1000);
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

void	start_dinner(t_philo *philo)
{
	int	i;

	philo->started_time = get_time();
	i = 0;
	while(i < philo->n_of_philos)
	{
		philo->time_started_to_eat[i] = philo->started_time;
		i++;
	}
	philo->all_philos_created = TRUE;
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
	usleep(1000);
	start_dinner(philo);
	i = 0;
}

void	wait_philo_die(t_philo *philo)
{
	int	i;
	
	while (!philo->is_anyone_dead)
		;
	philo->is_over = TRUE;
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
	philo->time_started_to_eat = ft_calloc(philo->n_of_philos, sizeof(long long));
	check_mem_alloc(philo, &philo->mem_alloc.ptr_mem_list, philo->time_started_to_eat, "ft_calloc failed");
	philo->threads = ft_calloc(philo->n_of_philos, sizeof(pthread_t));
	check_mem_alloc(philo, &philo->mem_alloc.ptr_mem_list, philo->threads, "ft_calloc failed");
	create_all_mutex(philo);
	ft_printf(1, "Numero de philosofos: %d\n", philo->n_of_philos);
	ft_printf(1, "tempo para morrer: %d\n", philo->time_to_die);
	ft_printf(1, "tempo para comer: %d\n", philo->time_to_eat);
	ft_printf(1, "tempo para dormir: %d\n", philo->time_to_sleep);
	if (argc == 6)
		ft_printf(1, "nº de vezes que cada filosofo deve comer: %d\n", \
			philo->n_of_times_to_eat);
	create_all_philos(philo);
	wait_philo_die(philo);
	destroy_all(philo);
	free_all(philo);
	return (0);
}