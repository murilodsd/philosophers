/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 03:24:16 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/26 04:59:30 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return(1000 * tv.tv_sec + tv.tv_usec / 1000);
}

/* int main(int argc, char const *argv[])
{
	int	start_time;
	
	start_time = get_time();
	sleep(1);
	ft_printf(1,"%d",(get_time() - start_time));
	return (0);
} */
