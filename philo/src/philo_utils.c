/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 03:24:16 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/23 19:38:35 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000);
}

void	ft_msleep(t_philo *philo, long msec)
{
	long long	started_time;

	(void)philo;
	started_time = get_time();
	usleep(msec * 1000 - 5000);
	while (get_time() - started_time < msec)
		usleep(500);
}

void	give_way(t_threads_params *threads_params)
{
	if (threads_params->philo->n_of_philos == 3)
		usleep(1000);
	else if (threads_params->eat_count % 2 == 0)
		usleep(20000);
}

void	init_bool_pointer(t_philo **philo)
{
	int		n_of_philos;
	t_list	**ptr_list;

	ptr_list = &(*philo)->mem_alloc.ptr_mem_list;
	n_of_philos = (*philo)->n_of_philos;
	(*philo)->time_started_to_eat_initialized = \
		ft_calloc(n_of_philos, sizeof(bool));
	check_mem_alloc((*philo), ptr_list, \
		(*philo)->time_started_to_eat_initialized, "ft_calloc failed");
	(*philo)->is_philo_enough_fed = ft_calloc(n_of_philos, sizeof(bool));
	check_mem_alloc((*philo), ptr_list, (*philo)->is_philo_enough_fed, \
		"ft_calloc failed");
	(*philo)->is_philo_enough_fed_mutex_initialized = \
		ft_calloc(n_of_philos, sizeof(bool));
	check_mem_alloc((*philo), ptr_list, \
		(*philo)->is_philo_enough_fed_mutex_initialized, "ft_calloc failed");
	(*philo)->forks_mutex_initialized = ft_calloc(n_of_philos, sizeof(bool));
	check_mem_alloc((*philo), ptr_list, (*philo)->forks_mutex_initialized, \
		"ft_calloc failed");
}

/* int main(int argc, char const *argv[])
{
	int	started_time;
	int 	i;

	started_time = get_time();
	i = 1;
	while (i < 100)
	{
		ft_msleep(10);
		i++;
	}
	ft_printf(1,"%d",(get_time() - started_time));
	return (0);
} */
