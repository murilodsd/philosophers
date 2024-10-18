/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mem_alloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:35:29 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/18 12:51:11 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
static void	save_pointer(t_philo *philo, \
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
 * ATENTION! THE POINTERS TO THE MEM LISTS MUST BE INITIALIZED TO NULL BEFORE USE
 * 
 * IF YOU HAVE A MEM ALLOC TO A POINTER TO A STRUCT THAT MANAGE ALL THE PROGRAM 
 * DO NOT CHECK THAT MEM ALLOC
 *
 * @param philo A pointer to the `t_philo` structure, 
 * which contains program state and memory allocation information.
 * @param ptr_or_matrix_list A double pointer to a list
 * where the allocated pointer will be saved.
 * @param ptr The pointer to the allocated memory to be checked.
 * @param error_msg A string containing the error message to be displayed
 * if the allocation fails.
 */
void	check_mem_alloc(t_philo *philo, t_list **ptr_or_matrix_list, \
	void *ptr, char *error_msg)
{
	if (!ptr)
		destroy_free_exit_error(philo, error_msg);
	else
		save_pointer(philo, ptr_or_matrix_list, ptr);
}
