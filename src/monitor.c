/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:08:23 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/15 05:01:54 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_time_philo_started_to_eat(t_threads_params *threads_params)
{
	long long	*time_started_to_eat;

	time_started_to_eat = threads_params->philo->time_started_to_eat;
	time_started_to_eat[threads_params->number - 1] = get_time();
}


/*Por fazermos a checagem se o programa terminou (ou por morte ou porque todos já foram alimentado)
somente no início de cada ação (eat, sleep e think), pois uma vez dentro dessa ação,
precisamos garantir que ela chegue até o final, para que os mutex sejam liberados. Portanto,
pode ocorrer de uma thread estar presa em um mutex e a condição de fim do programa acabar, assim
após o mutex ser liberado, ela acabaria "executando as ações", por isso
precisamos colocar a condição de nada ser feito no início.*/
void	print_action(t_threads_params *threads_params, char *msg, bool is_eating)
{
	long	time_now;

	if (threads_params->philo->is_over == TRUE)
		return ;
	pthread_mutex_lock(&threads_params->philo->print_mutex);
	if (is_eating == TRUE)
		set_time_philo_started_to_eat(threads_params);
	time_now = get_time() - threads_params->philo->started_time;
	ft_printf(1, msg, time_now, threads_params->number);
	pthread_mutex_unlock(&threads_params->philo->print_mutex);
}

void	print_death(t_philo *philo, int philo_number)
{
	long	time_now;

	pthread_mutex_lock(&philo->print_mutex);
	time_now = get_time() - philo->started_time;
	ft_printf(1, RED "%d %d died\n" RESET, time_now, philo_number);
	pthread_mutex_unlock(&philo->print_mutex);
}

void	print_debug(t_philo *philo, char *msg)
{
	long	time_now;

	pthread_mutex_lock(&philo->print_mutex);
	time_now = get_time() - philo->started_time;
	ft_printf(1, msg);
	pthread_mutex_unlock(&philo->print_mutex);
}

void	get_forks(t_threads_params *threads_params, pthread_mutex_t *left_fork_mutex, pthread_mutex_t *right_fork_mutex)
{
	check_program_is_over(threads_params->philo);
	pthread_mutex_lock(left_fork_mutex);
	print_action(threads_params, "%d %d has taken a fork\n", FALSE);
	pthread_mutex_lock(right_fork_mutex);
	print_action(threads_params, "%d %d has taken a fork\n", FALSE);
	print_action(threads_params, "%d %d is eating\n", TRUE);
	ft_msleep(philo, threads_params->philo->time_to_eat);
	pthread_mutex_unlock(right_fork_mutex);
	pthread_mutex_unlock(left_fork_mutex);
}

void	start_to_sleep(t_threads_params *threads_params)
{
	check_program_is_over(threads_params->philo);
	print_action(threads_params, "%d %d is sleeping\n", FALSE);
	ft_msleep(philo, threads_params->philo->time_to_sleep);
}

void	start_to_think(t_threads_params *threads_params)
{
	check_program_is_over(threads_params->philo);
	print_action(threads_params, "%d %d is thinking\n", FALSE);
}
/* int main(int argc, char const *argv[])
{
	print_action(NULL, "Philo %d got the left fork %d\n", 1, 2);
	return 0;
} */

