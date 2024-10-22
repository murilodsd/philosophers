/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:08:23 by mde-souz          #+#    #+#             */
/*   Updated: 2024/10/22 18:03:52 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*Fazemos a checagem se o programa terminou (ou por morte ou
porque todos já foram alimentado) somente no início de 
cada ação (eat, sleep e think), afim de garantir que
ela chegue até o final e os mutex sejam liberados
não ocorrendo assim de outra thread ficar presa nesse mutex. 
Por fazermos essa checagem somente no inicio, a ação poderia acabar executando
algumas tarefas mesmo depois de já cumprida a condição de termino de program
Portanto Se faz necessário verificar a condição de término do programa
antes de cada de uma dessas tarefas da ação..*/
void	print_action(t_threads_params *threads_params, char *msg, \
	bool is_eating)
{
	long	time_now;
	t_philo	*philo;

	philo = threads_params->philo;
	if (is_eating == TRUE)
		set_time_philo_started_to_eat(philo, \
			threads_params->number, get_time());
	pthread_mutex_lock(&threads_params->philo->print_mutex);
	time_now = get_time() \
		- philo->started_time;
	if (!get_is_over(threads_params->philo))
		printf(msg, time_now, threads_params->number);
	pthread_mutex_unlock(&threads_params->philo->print_mutex);
}

void	print_death(t_philo *philo, int philo_number)
{
	long	time_now;

	pthread_mutex_lock(&philo->print_mutex);
	time_now = get_time() - philo->started_time;
	printf("%ld %d died\n", time_now, philo_number);
	pthread_mutex_unlock(&philo->print_mutex);
}

void	get_forks(t_threads_params *threads_params, \
	pthread_mutex_t *left_fork_mutex, pthread_mutex_t *right_fork_mutex)
{
	check_program_is_over(threads_params->philo);
	if (threads_params->number % 2 == 1)
		pthread_mutex_lock(left_fork_mutex);
	else
		pthread_mutex_lock(right_fork_mutex);
	print_action(threads_params, "%d %d has taken a fork\n", FALSE);
	if (threads_params->number % 2 == 1)
		pthread_mutex_lock(right_fork_mutex);
	else
		pthread_mutex_lock(left_fork_mutex);
	print_action(threads_params, "%d %d has taken a fork\n", FALSE);
	print_action(threads_params, "%d %d is eating\n", TRUE);
	ft_msleep(threads_params->philo, threads_params->philo->time_to_eat);
	if (threads_params->number % 2 == 1)
		pthread_mutex_unlock(left_fork_mutex);
	else
		pthread_mutex_unlock(right_fork_mutex);
	if (threads_params->number % 2 == 1)
		pthread_mutex_unlock(right_fork_mutex);
	else
		pthread_mutex_unlock(left_fork_mutex);
	threads_params->eat_count++;
	check_i_am_enough_fed(threads_params);
}

void	start_to_sleep(t_threads_params *threads_params)
{
	print_action(threads_params, "%d %d is sleeping\n", FALSE);
	ft_msleep(threads_params->philo, threads_params->philo->time_to_sleep);
}

void	start_to_think(t_threads_params *threads_params)
{
	print_action(threads_params, "%d %d is thinking\n", FALSE);
	if (threads_params->philo->n_of_philos % 2 == 1)
		give_way(threads_params);
}
/* int main(int argc, char const *argv[])
{
	print_action(NULL, "Philo %d got the left fork %d\n", 1, 2);
	return 0;
} */
