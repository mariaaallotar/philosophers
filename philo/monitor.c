/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:37:26 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/16 16:30:26 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	died_of_hunger(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared_info->lock));
	// if (philo->philo_num == 4)
	// 	printf("Checking if should die when time since last meal is %i\n", (int)(get_time() - philo->last_meal));
	if ((int)(get_time() - philo->last_meal) > philo->shared_info->time_to_die)
	{
		philo->shared_info->somebody_died = philo->philo_num;
		pthread_mutex_unlock(&(philo->shared_info->lock));
		return (1);
	}
	pthread_mutex_unlock(&(philo->shared_info->lock));
	return (0);
}

int	monitor_philos(t_info *info, t_philo **philos)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < info->num_of_philos)
		{
			if (died_of_hunger(philos[i]))
				break ;
			i++;
		}
		if (should_stop(info))
			break ;
	}
	join_threads(philos, info);
	return (0);
}
