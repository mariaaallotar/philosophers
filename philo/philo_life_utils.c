/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:09:53 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/02 16:12:57 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long   time_since_last_meal(t_philo philo)
{
	struct timeval now;
	unsigned long	seconds;
	long	microseconds;
	unsigned long	milliseconds;

	gettimeofday(&now, NULL);
	seconds = now.tv_sec - philo.last_meal.tv_sec;
	if (now.tv_usec < philo.last_meal.tv_usec)
	{
		seconds--;
		microseconds = (now.tv_usec + 1000000) - philo.last_meal.tv_usec;
	}
	else
	{
		microseconds = now.tv_usec - philo.last_meal.tv_usec;
	}
	milliseconds = (seconds * 1000) + (microseconds / 1000);
	return (milliseconds);
}

int	died_of_hunger(t_philo *philo)
{
	// printf("In died of hunger: time since eaten: %lu, time to die: %i\n", time_since_last_meal(philo), philo.shared_info->time_to_die);
	if (time_since_last_meal(*philo) > (unsigned long) philo->shared_info->time_to_die)
	{
		// printf("-------------------------------------------------\n");
		// printf("%i set in somebody died\n", philo.philo_num);
		philo->shared_info->somebody_died = philo->philo_num;
		return (1);
	}
	return (0);
}

void	philo_print(t_info *info, int philo_num, char *message)
{
	printf("%lu %i %s\n", milliseconds_since_start(info), philo_num, message);
}

int	time_to_stop(t_philo *philo)
{
	if (philo->shared_info->somebody_died)
		return (1);
	if (died_of_hunger(philo))
		return (1);
	return (0);
}

int	dynamic_sleep(t_philo *philo, int time_to_do)
{
	unsigned long	start;

	start = milliseconds_since_start(philo->shared_info);
	while ((milliseconds_since_start(philo->shared_info) - start)
		< (unsigned long) time_to_do)
	{
		usleep(500);
		if (time_to_stop(philo))
			return (-1);
	}
	return (0);
}
