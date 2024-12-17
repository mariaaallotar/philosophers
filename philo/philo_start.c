/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:43:16 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/17 15:30:55 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo_edge(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo_print(philo->shared_info, philo->philo_num, "has taken a fork");
	dynamic_wait(philo, philo->shared_info->time_to_die);
	pthread_mutex_lock(&(philo->shared_info->lock));
	philo->shared_info->somebody_died = 1;
	pthread_mutex_unlock(&(philo->shared_info->lock));
	pthread_mutex_unlock(philo->left_fork);
}

void	synchronize_philos(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->lock));
	while (info->start == 0)
	{
		pthread_mutex_unlock(&(info->lock));
		usleep(1);
		pthread_mutex_lock(&(info->lock));
	}
	philo->last_meal = info->start_time;
	pthread_mutex_unlock(&(info->lock));
}

int	stagger_philos(t_philo *philo)
{
	if (philo->philo_num % 2 == 1)
	{
		if (dynamic_wait(philo, 5) == -1)
			return (-1);
	}
	return (1);
}

void	*philo_start(void *args)
{
	t_philo	*philo;

	philo = (t_philo *) args;
	if (philo->shared_info->num_of_philos == 1)
	{
		one_philo_edge(philo);
		return (NULL);
	}
	synchronize_philos(philo->shared_info, philo);
	if (stagger_philos(philo) == -1)
		return (NULL);
	philo_life(philo);
	return (NULL);
}
