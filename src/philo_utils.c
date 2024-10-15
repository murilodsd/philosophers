/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 03:24:16 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/15 05:02:35 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return((long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000);
}

void	ft_msleep(t_philo *philo, long msec)
{
	long long	started_time;
	
	if (philo->is_over == TRUE)
		return ;
	started_time = get_time();
	while (get_time() - started_time < msec)
		usleep(100);
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
