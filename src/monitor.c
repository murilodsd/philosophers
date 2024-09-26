/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:08:23 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/25 17:59:18 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *msg, int philo_number, int fork_number)
{
	pthread_mutex_lock(&philo->print_mutex);
	ft_printf(1, msg, philo_number, fork_number);
	pthread_mutex_unlock(&philo->print_mutex);
}

/* int main(int argc, char const *argv[])
{
	print_action(NULL, "Philo %d got the left fork %d\n", 1, 2);
	return 0;
} */

