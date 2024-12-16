/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:32:42 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/16 15:43:22 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    enough_eats(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared_info->lock));
	philo->shared_info->philos_finished++;
	if (philo->shared_info->philos_finished ==
		philo->shared_info->num_of_philos)
	{
		 pthread_mutex_unlock(&(philo->shared_info->lock));
		 return (-1);
	}
	pthread_mutex_unlock(&(philo->shared_info->lock));
	return (1);
}

int	philo_think(t_philo *philo)
{
	philo_print(philo->shared_info, philo->philo_num, "is thinking");
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	philo_print(philo->shared_info, philo->philo_num, "is sleeping");
	if (dynamic_wait(philo, philo->shared_info->time_to_sleep) == -1)
		return (-1);
	return (1);
}

int stagger_philos(t_philo *philo)
{
	if (philo->philo_num % 2 == 1)
	{
		if (dynamic_wait(philo, 55) == -1)
			return (-1);
	}
	return (1);
}

void    philo_life(t_philo *philo)
{
	int i;

	i = 0;
	if (stagger_philos(philo) == -1)
		return ;
	while (1)
	{
		if (i > 0)
		{
			if (philo_think(philo) == -1)
				break ;
		}
		if (philo_eat(philo) == -1)
			break ;
		i++;
		if (i == philo->shared_info->minimum_eats)
		{
			if (enough_eats(philo) == -1)
				break ;
		}
		if (philo_sleep(philo) == -1)
			break ;
	}
}
