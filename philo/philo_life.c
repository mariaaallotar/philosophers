/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:51:22 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/09 13:33:26 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo_edge(t_philo	*philo)
{
	int	left_fork;

	philo_print(philo->shared_info, philo->philo_num, "is thinking");
	left_fork = philo->philo_num - 1;
	pthread_mutex_lock(&(philo->shared_info->forks[left_fork]));
	philo_print(philo->shared_info, philo->philo_num, "has taken a fork");
	dynamic_sleep(philo, philo->shared_info->time_to_die);
	philo->shared_info->somebody_died = 1;
	gettimeofday(&(philo->shared_info->death_time), NULL);
	pthread_mutex_unlock(&(philo->shared_info->forks[left_fork]));
}

void    *philo_life(void *args)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *) args;
	if (philo->shared_info->num_of_philos == 1)
	{
		one_philo_edge(philo);
		return (NULL);
	}
	i = 0;
	while (1)
	{
		if (philo_think(philo) == -1)
			break ;
		if (i == 0 && philo->philo_num % 2 == 1)
			usleep (philo->shared_info->time_to_eat / 2);
		if (time_to_stop(philo))
			break ;
		if (philo_eat(philo) == -1)
			break ;
		if (time_to_stop(philo))
			break ;
		i++;
		if (i == philo->shared_info->minimum_eats)
		{
			pthread_mutex_lock(&(philo->shared_info->data_lock));
			philo->shared_info->philos_finished++;
			pthread_mutex_unlock(&(philo->shared_info->data_lock));
		}
		if (philo_sleep(philo) == -1)
			break ;
	}
	return (&(philo->shared_info->somebody_died));
}
