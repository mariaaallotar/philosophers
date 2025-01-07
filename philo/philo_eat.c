/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:37:57 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/18 10:56:47 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (should_stop(philo->shared_info))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (-1);
	}
	philo_print(philo->shared_info, philo->philo_num, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	if (should_stop(philo->shared_info))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
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
	pthread_mutex_lock(&(philo->shared_info->lock));
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(philo->shared_info->lock));
	if (dynamic_wait(philo, philo->shared_info->time_to_eat) == -1)
	{
		philo_release_forks(philo);
		return (-1);
	}
	philo_release_forks(philo);
	should_stop(philo->shared_info);
	return (1);
}
