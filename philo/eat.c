/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:34:41 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/10 16:05:15 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	take_fork_even(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (time_to_stop(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (-1);
	}
	philo_print(philo->shared_info, philo->philo_num, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	if (time_to_stop(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (-1);
	}
	philo_print(philo->shared_info, philo->philo_num, "has taken a fork");
	return (1);
}

int	take_fork_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (time_to_stop(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (-1);
	}
	philo_print(philo->shared_info, philo->philo_num, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	if (time_to_stop(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (-1);
	}
	philo_print(philo->shared_info, philo->philo_num, "has taken a fork");
	return (1);
}

int	philo_take_forks(t_philo *philo)
{
	if (philo->philo_num % 2 == 0)
		return (take_fork_even(philo));
	if (philo->philo_num % 2 == 1)
		return (take_fork_odd(philo));
	return (-1);
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
