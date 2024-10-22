/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 03:24:16 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/22 10:14:35 by mde-souz         ###   ########.fr       */
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
	//bool		is_over;

	/* is_over = safe_get_bool(&philo->is_over_mutex, &philo->is_over);
	if (is_over == TRUE)
		return ; */
	(void)philo;
	started_time = get_time();
	usleep(msec * 1000 - 5000);
	while (get_time() - started_time < msec)
		usleep(500);
}

void	give_way(t_threads_params *threads_params)
{
	if (threads_params->eat_count % 2 == 0)
		usleep(20000);
		//edited
		//ft_msleep(threads_params->philo, threads_params->philo->time_to_eat/2 + 10);
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
