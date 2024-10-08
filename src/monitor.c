/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:08:23 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/02 10:38:38 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_threads_params *threads_params, char *msg)
{
	int	time;

	time = get_time() - threads_params->philo->start_time;
	if (ft_strnstr(msg, "eating", ft_strlen(msg)))
		threads_params->time_started_to_eat = time;
	pthread_mutex_lock(&threads_params->philo->print_mutex);
	ft_printf(1, msg, time, threads_params->number);
	pthread_mutex_unlock(&threads_params->philo->print_mutex);
}

void	get_forks(t_threads_params *threads_params, pthread_mutex_t *left_fork_mutex, pthread_mutex_t *right_fork_mutex)
{
	if (threads_params->number % 2 == 1)
	{
		pthread_mutex_lock(left_fork_mutex);
		print_action(threads_params, "%d %d has taken a fork\n");
		pthread_mutex_lock(right_fork_mutex);
		print_action(threads_params, "%d %d has taken a fork\n");
		print_action(threads_params, "%d %d is eating\n");
		usleep(1000 * threads_params->philo->time_to_eat);
		pthread_mutex_unlock(right_fork_mutex);
		pthread_mutex_unlock(left_fork_mutex);
	}
	else
	{
		pthread_mutex_lock(right_fork_mutex);
		print_action(threads_params, "%d %d has taken a fork\n");
		pthread_mutex_lock(left_fork_mutex);
		print_action(threads_params, "%d %d has taken a fork\n");
		print_action(threads_params, "%d %d is eating\n");
		usleep(1000 * threads_params->philo->time_to_eat);
		pthread_mutex_unlock(left_fork_mutex);
		pthread_mutex_unlock(right_fork_mutex);
	}
}

void	start_to_sleep(t_threads_params *threads_params)
{
	print_action(threads_params, "%d %d is sleeping\n");
	usleep(1000 * threads_params->philo->time_to_sleep);
}

void	start_to_think(t_threads_params *threads_params)
{
	print_action(threads_params, "%d %d is thinking\n");
}
/* int main(int argc, char const *argv[])
{
	print_action(NULL, "Philo %d got the left fork %d\n", 1, 2);
	return 0;
} */

