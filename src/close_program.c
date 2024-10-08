/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 04:27:17 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/27 14:03:54 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_free_exit_error(t_philo *philo, char *error_msg)
{
	if (errno)
		ft_printf(2, "Error\n%s: %s\n", error_msg, strerror(errno));
	else
		ft_printf(2, "Error\n%s\n", error_msg);
	destroy_all(philo);
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

void	destroy_all(t_philo *philo)
{
	int	i;

	if (philo->print_mutex_initialized)
		pthread_mutex_destroy(&philo->print_mutex);
	if (philo->forks)
	{
		i = 0;
		while(i < philo->n_of_philos)
		{
			if (&philo->forks[i])
				pthread_mutex_destroy(&philo->forks[i]);
			i++;
		}
	}
}

/**
 * @brief Saves a pointer in a linked list.
 *
 * This function creates a new node with the given pointer and adds it to the 
 * front of the provided linked list. If memory allocation for the new node 
 * fails, it calls the destroy_free_exit_error function to handle the error.
 *
 * @param philo A pointer to the t_philo structure, used for error handling.
 * @param ptr_or_matrix_list A double pointer to the head of the linked list 
 * where the new node will be added.
 * @param ptr The pointer to be saved in the new node.
 */
void	save_pointer(t_philo *philo, \
	t_list **ptr_or_matrix_list, void *ptr)
{
	t_list	*new_node;

	new_node = ft_lstnew(ptr);
	if (!new_node)
		destroy_free_exit_error(philo, "Failed to allocate mem for a node");
	ft_lstadd_front(ptr_or_matrix_list, new_node);
}

/**
 * @brief Checks if memory allocation was successful and handles errors.
 *
 * ATTENTION!  THE POINTERS TO THE MEMORY LISTS MUST BE INITIALIZED TO NULL BEFORE USE
 * IF YOU HAVE A MEM ALLOC TO A POINTER TO A STRUCT THAT MANAGE ALL THE PROGRAM DO NOT CHECK THAT MEM ALLOC
 *
 * @param philo A pointer to the `t_philo` structure, which contains program state and memory allocation information.
 * @param ptr_or_matrix_list A double pointer to a list where the allocated pointer will be saved.
 * @param ptr The pointer to the allocated memory to be checked.
 * @param error_msg A string containing the error message to be displayed if the allocation fails.
 */
void	check_mem_alloc(t_philo *philo, t_list **ptr_or_matrix_list, void *ptr, char *error_msg)
{
	if (!ptr)
		destroy_free_exit_error(philo, error_msg);
	else
		save_pointer(philo, ptr_or_matrix_list, ptr);
}

