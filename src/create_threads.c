/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 05:06:18 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/23 22:13:13 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*pthread_created(void *params)
{
	t_philo	*philo;
	int	left_fork_index;
	int	right_fork_index;

	philo = (t_philo *)params;
	//ft_printf(1, "Philo number %d\n", philo->number);
	left_fork_index = philo->number - 1;
	if (philo->number == 1)
		right_fork_index = philo->n_of_philos - 1;
	else
		right_fork_index = philo->number - 2;
	//ft_printf(1, "Philo %d created, Garfo da direita %d, Garfo da esquerda %d\n", philo->number, right_fork_index + 1, left_fork_index + 1);

	if (philo->number % 2 == 1)
	{
		pthread_mutex_lock(&philo->forks[left_fork_index]);
		ft_printf(1, "Philo %d got the left fork %d\n", philo->number, left_fork_index + 1);
		pthread_mutex_lock(&philo->forks[right_fork_index]);
		ft_printf(1, "Philo %d got the right fork %d\n", philo->number, right_fork_index + 1);
		sleep(2);
		ft_printf(1, "Philo %d left the left fork %d\n", philo->number, left_fork_index + 1);
		ft_printf(1, "Philo %d left the right fork %d\n", philo->number, right_fork_index + 1);
		pthread_mutex_unlock(&philo->forks[left_fork_index]);
		pthread_mutex_unlock(&philo->forks[right_fork_index]);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[right_fork_index]);
		ft_printf(1, "Philo %d got the right fork %d\n", philo->number, right_fork_index + 1);
		pthread_mutex_lock(&philo->forks[left_fork_index]);
		ft_printf(1, "Philo %d got the left fork %d\n", philo->number, left_fork_index + 1);
		sleep(2);
		ft_printf(1, "Philo %d left the right fork %d\n", philo->number, right_fork_index + 1);
		ft_printf(1, "Philo %d left the left fork %d\n", philo->number, left_fork_index + 1);
		pthread_mutex_unlock(&philo->forks[right_fork_index]);
		pthread_mutex_unlock(&philo->forks[left_fork_index]);
	}
	pthread_exit(NULL);	
}
void	create_philo(t_philo *philo, int index)
{
	philo->number = index + 1;
	//ft_printf(1, "entrou no create philo number %d\n", philo->number);
	pthread_create(&philo->threads[index], NULL, pthread_created, &philo[index]);	
}


void	create_all_philos(t_philo *philo)
{
	int	i;
	
	i = 0; 
	while(i < philo->n_of_philos)
	{	
		create_philo(&philo[i], i);
		i++;
	}
	while(i < philo->n_of_philos)
		pthread_join(philo->threads[i++], NULL);
}

int	main(int argc, char *argv[])
{
	t_philo	*philo;
	
	get_arguments_and_init(argc, argv, &philo);
	create_all_mutex(philo);
	ft_printf(1, "Numero de philosofos: %d\n", philo->n_of_philos);
	ft_printf(1, "tempo para morrer: %d\n", philo->time_to_die);
	ft_printf(1, "tempo para comer: %d\n", philo->time_to_eat);
	ft_printf(1, "tempo para dormir: %d\n", philo->time_to_sleep);
	if (argc == 6)
		ft_printf(1, "nº de vezes que cada filosofo deve comer: %d\n", \
			philo->n_of_times_to_eat);
	create_all_philos(philo);
	sleep(6);	
	return (0);
}