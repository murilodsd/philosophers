/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 03:24:16 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/10 19:57:07 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return((long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000);
}

void	ft_msleep(long msec)
{
	long long	started_time;
	
	started_time = get_time();
	while (get_time() - started_time < msec)
		usleep(500);
}


/* int main(int argc, char const *argv[])
{
	int	start_time;
	int 	i;

	start_time = get_time();
	i = 1;
	while (i < 100)
	{
		ft_msleep(10);
		i++;
	}
	ft_printf(1,"%d",(get_time() - start_time));
	return (0);
} */
