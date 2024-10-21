/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 05:06:18 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/20 14:31:58 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	handle_one_philo(t_threads_params *threads_params)
{
	pthread_mutex_lock(&threads_params->philo->forks[0]);
	print_action(threads_params, "%d %d has taken a fork\n", FALSE);
	while (!get_is_over(threads_params->philo))
		;
	pthread_mutex_unlock(&threads_params->philo->forks[0]);
	pthread_exit(NULL);
}

static void	*pthread_created(void *params)
{
	t_threads_params	*tparams;
	int					left_fork_index;
	int					right_fork_index;

	tparams = (t_threads_params *)params;
	left_fork_index = tparams->number - 1;
	if (tparams->number == 1)
		right_fork_index = tparams->philo->n_of_philos - 1;
	else
		right_fork_index = tparams->number - 2;
	while (!get_is_all_philo_created(tparams))
		;
	if (tparams->number % 2 == 0)
		usleep(20000);
	if (tparams->philo->n_of_philos == 1)
		handle_one_philo(tparams);
	while (1)
	{
		get_forks(tparams, &tparams->philo->forks[left_fork_index], \
			&tparams->philo->forks[right_fork_index]);
		start_to_sleep(tparams);
		start_to_think(tparams);
	}
	return (NULL);
}

static void	create_philo(t_philo *philo, int index)
{
	t_threads_params	*threads_params;

	threads_params = ft_calloc(1, sizeof(t_threads_params));
	check_mem_alloc(philo, &philo->mem_alloc.ptr_mem_list, threads_params, \
		"Malloc failed");
	threads_params->number = index + 1;
	threads_params->philo = philo;
	threads_params->eat_count = 0;
	pthread_create(&philo->threads[index], NULL, pthread_created, \
		threads_params);
}

static void	start_dinner(t_philo *philo)
{
	int	i;

	philo->started_time = get_time();
	i = 0;
	while (i < philo->n_of_philos)
	{
		set_time_philo_started_to_eat(philo, i + 1, philo->started_time);
		i++;
	}
	set_all_threads_created(philo);
}

void	create_all_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->n_of_philos)
	{
		create_philo(philo, i);
		i++;
	}
	usleep(2000);
	start_dinner(philo);
}
