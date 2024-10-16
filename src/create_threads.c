/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 05:06:18 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/16 08:23:17 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_program_is_over(t_philo *philo)
{
	bool	is_over;

	is_over = safe_get_bool(&philo->is_over_mutex,&philo->is_over);
	if (is_over == TRUE)
		pthread_exit(NULL);
}

bool	check_all_philo_created(t_threads_params *threads_params)
{
	return (safe_get_bool(&threads_params->philo->is_all_philos_created_mutex, \
		&threads_params->philo->is_all_philos_created));
}

void	*pthread_created(void *params)
{
	t_threads_params	*threads_params;
	int	left_fork_index;
	int	right_fork_index;

	threads_params = (t_threads_params *)params;
	left_fork_index = threads_params->number - 1;
	if (threads_params->number == 1)
		right_fork_index = threads_params->philo->n_of_philos - 1;
	else
		right_fork_index = threads_params->number - 2;
	while (!check_all_philo_created(threads_params))
		;
	if (threads_params->number % 2 == 0)
		usleep(1000);
	if (threads_params->philo->n_of_philos == 1)
	{
		pthread_mutex_lock(&threads_params->philo->forks[left_fork_index]);
		print_action(threads_params, "%d %d has taken a fork\n", FALSE);
		while (!safe_get_bool(&threads_params->philo->is_over_mutex,&threads_params->philo->is_over))
			;
		pthread_mutex_unlock(&threads_params->philo->forks[left_fork_index]);
		pthread_exit(NULL);
	}
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
	check_mem_alloc(philo, &philo->mem_alloc.ptr_mem_list, threads_params, "Malloc failed");
	threads_params->number = index + 1;
	threads_params->philo = philo;
	threads_params->eat_count = 0;
	pthread_create(&philo->threads[index], NULL, pthread_created, threads_params);	
}

void	set_all_threads_created(t_philo *philo)
{
	safe_set_bool(&philo->is_all_philos_created_mutex, &philo->is_all_philos_created, TRUE);
}

void	start_dinner(t_philo *philo)
{
	int	i;

	philo->started_time = get_time();
	i = 0;
	while(i < philo->n_of_philos)
	{
		safe_set_long_long(&philo->is_all_philos_created_mutex, &philo->time_started_to_eat[i], philo->started_time);
		i++;
	}
	set_all_threads_created(philo);
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
}
