/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:08:23 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/08 20:48:11 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_time_philo_started_to_eat(t_threads_params *threads_params, long time_now)
{
	long	*time_started_to_eat;

	time_started_to_eat = threads_params->philo->time_started_to_eat;
	time_started_to_eat[threads_params->number - 1] = time_now;
}

void	print_action(t_threads_params *threads_params, char *msg, bool is_eating)
{
	long	time_now;

	pthread_mutex_lock(&threads_params->philo->print_mutex);
	time_now = get_time() - threads_params->philo->start_time;
	if (is_eating == TRUE)
		set_time_philo_started_to_eat(threads_params, time_now);
	ft_printf(1, msg, time_now, threads_params->number);
	pthread_mutex_unlock(&threads_params->philo->print_mutex);
}

void	get_forks(t_threads_params *threads_params, pthread_mutex_t *left_fork_mutex, pthread_mutex_t *right_fork_mutex)
{
		pthread_mutex_lock(left_fork_mutex);
		print_action(threads_params, "%d %d has taken a fork\n", FALSE);
		pthread_mutex_lock(right_fork_mutex);
		print_action(threads_params, "%d %d has taken a fork\n", FALSE);
		print_action(threads_params, "%d %d is eating\n", TRUE);
		usleep(1000 * threads_params->philo->time_to_eat);
		pthread_mutex_unlock(right_fork_mutex);
		pthread_mutex_unlock(left_fork_mutex);
}

void	start_to_sleep(t_threads_params *threads_params)
{
	print_action(threads_params, "%d %d is sleeping\n", FALSE);
	usleep(1000 * threads_params->philo->time_to_sleep);
}

void	start_to_think(t_threads_params *threads_params)
{
	print_action(threads_params, "%d %d is thinking\n", FALSE);
}
/* int main(int argc, char const *argv[])
{
	print_action(NULL, "Philo %d got the left fork %d\n", 1, 2);
	return 0;
} */

