/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:04:36 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/18 10:23:49 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop(t_info *shared_info)
{
	pthread_mutex_lock(&(shared_info->lock));
	if (shared_info->somebody_died)
	{
		pthread_mutex_unlock(&(shared_info->lock));
		return (1);
	}
	if (shared_info->philos_finished >= shared_info->num_of_philos)
	{
		pthread_mutex_unlock(&(shared_info->lock));
		return (1);
	}
	pthread_mutex_unlock(&(shared_info->lock));
	return (0);
}

size_t	get_time(void)
{
	struct timeval	time;
	size_t			result;
	int				ret;

	ret = gettimeofday(&time, NULL);
	if (ret == -1)
	{
		error_message("Failed to get current time, "
			"unexpected behaviour expected\n");
		return (-1);
	}
	result = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	return (result);
}

int	dynamic_wait(t_philo *philo, int time_to_do)
{
	size_t	end_time;

	end_time = get_time() + time_to_do;
	while (get_time() < end_time)
	{
		if (should_stop(philo->shared_info))
			return (-1);
		usleep(500);
	}
	return (0);
}

void	philo_print(t_info *info, int philo_num, char *message)
{
	int	now;

	pthread_mutex_lock(&(info->print_lock));
	now = get_time() - info->start_time;
	printf("%i %i %s\n", now, philo_num, message);
	pthread_mutex_unlock(&(info->print_lock));
}
