/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:08:44 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/18 13:37:33 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_debug(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->print_mutex);
	ft_printf(1, msg);
	pthread_mutex_unlock(&philo->print_mutex);
}
