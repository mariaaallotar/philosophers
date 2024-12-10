/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:09:53 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/10 16:17:17 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long   event_at_milliseconds(struct timeval event, t_info info)
{
	unsigned long	seconds;
	long	microseconds;
	unsigned long	milliseconds;

	seconds = event.tv_sec - info.start_time.tv_sec;
	if (event.tv_usec < info.start_time.tv_usec)
	{
		seconds--;
		microseconds = (event.tv_usec + 1000000) - info.start_time.tv_usec;
	}
	else
	{
		microseconds = event.tv_usec - info.start_time.tv_usec;
	}
	milliseconds = (seconds * 1000) + (microseconds / 1000);
	return (milliseconds);
}

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
	if (time_since_last_meal(*philo) > (unsigned long) philo->shared_info->time_to_die)
	{
		pthread_mutex_lock(&(philo->shared_info->data_lock));
		gettimeofday(&(philo->shared_info->death_time), NULL);
		philo->shared_info->somebody_died = philo->philo_num;
		pthread_mutex_unlock(&(philo->shared_info->data_lock));
		return (1);
	}
	return (0);
}

void	philo_print(t_info *info, int philo_num, char *message)
{
	pthread_mutex_lock(&(info->print_lock));
	printf("%lu %i %s\n", milliseconds_since_start(info), philo_num, message);
	pthread_mutex_unlock(&(info->print_lock));
}

int	time_to_stop(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared_info->data_lock));
	if (philo->shared_info->somebody_died)
	{
		pthread_mutex_unlock(&(philo->shared_info->data_lock));
		return (1);
	}
	if (philo->shared_info->minimum_eats > 0 &&
		philo->shared_info->philos_finished >= philo->shared_info->num_of_philos)
	{
		pthread_mutex_unlock(&(philo->shared_info->data_lock));
		return (1);
	}
	pthread_mutex_unlock(&(philo->shared_info->data_lock));
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
		{
			return (-1);
		}
	}
	return (0);
}
