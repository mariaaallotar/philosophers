/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:34:41 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/05 16:06:55 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_release_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->philo_num - 1;
	pthread_mutex_unlock(&(philo->shared_info->forks[left_fork]));
	if (philo->philo_num == philo->shared_info->num_of_philos)
		right_fork = 0;
	else
		right_fork = philo->philo_num;
	pthread_mutex_unlock(&(philo->shared_info->forks[right_fork]));
	//printf("%lu %i has released forks\n", get_current_time_milliseconds(philo_info), philo_info->philo_num);
}

int	philo_take_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->philo_num - 1;
	if (philo->philo_num == philo->shared_info->num_of_philos)
		right_fork = 0;
	else
		right_fork = philo->philo_num;
	pthread_mutex_lock(&(philo->shared_info->forks[left_fork]));
	if (time_to_stop(philo))
	{
		pthread_mutex_unlock(&(philo->shared_info->forks[left_fork]));
		return (-1);
	}
	philo_print(philo->shared_info, philo->philo_num, "has taken a fork");
	pthread_mutex_lock(&(philo->shared_info->forks[right_fork]));
	if (time_to_stop(philo))
	{
		pthread_mutex_unlock(&(philo->shared_info->forks[left_fork]));
		pthread_mutex_unlock(&(philo->shared_info->forks[right_fork]));
		return (-1);
	}
	philo_print(philo->shared_info, philo->philo_num, "has taken a fork");
	return (1);
}

int	philo_eat(t_philo *philo)
{
	if (philo_take_forks(philo) == -1)
		return (-1);
	philo_print(philo->shared_info, philo->philo_num, "is eating");
	gettimeofday(&(philo->last_meal), NULL);
	if (dynamic_sleep(philo, philo->shared_info->time_to_eat) == -1)
	{
		philo_release_forks(philo);
		return (-1);
	}
	philo_release_forks(philo);
	return (1);
}
