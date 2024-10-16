/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 04:27:17 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/16 16:43:25 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_free_exit_error(t_philo *philo, char *error_msg)
{
	if (errno)
		ft_printf(2, "Error\n%s: %s\n", error_msg, strerror(errno));
	else
		ft_printf(2, "Error\n%s\n", error_msg);
	destroy_all_mutex(philo);
	free_all(philo);
	exit(EXIT_FAILURE);
}

void	free_all(t_philo *philo)
{
	if (philo->mem_alloc.ptr_mem_list != NULL)
		ft_lstclear(&(philo->mem_alloc.ptr_mem_list), free);
	if (philo->mem_alloc.matrix_mem_list != NULL)
		ft_lstclear(&(philo->mem_alloc.matrix_mem_list), ft_free_matrix);
	free(philo);
}

static void	destroy_mutex(pthread_mutex_t *mutex, bool is_initialized)
{
	if (is_initialized)
		pthread_mutex_destroy(mutex);
}

void	destroy_all_mutex(t_philo *philo)
{
	int	i;

	destroy_mutex(&philo->print_mutex, philo->print_mutex_initialized);
	destroy_mutex(&philo->is_over_mutex, philo->is_over_mutex_initialized);
	destroy_mutex(&philo->is_anyone_dead_mutex, philo->is_anyone_dead_mutex_initialized);
	destroy_mutex(&philo->is_all_philos_created_mutex, philo->is_all_philos_created_mutex_initialized);
	destroy_mutex(&philo->is_philo_enough_fed_mutex, philo->is_philo_enough_fed_mutex_initialized);
	if (philo->forks)
	{
		i = 0;
		while(i < philo->n_of_philos)
		{
			if (&philo->forks[i])
				destroy_mutex(&philo->forks[i], TRUE);
			i++;
		}
	}
}

