/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:04:36 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/16 15:37:16 by maheleni         ###   ########.fr       */
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

size_t    get_time(void)
{
    struct timeval    time;
    size_t            result;

    gettimeofday(&time, NULL);
    result = (time.tv_usec / 1000) + (time.tv_sec * 1000);
    return (result);
}

int	dynamic_wait(t_philo *philo, int time_to_do)
{
	int	start;
	int	now;

	start = get_time();
	now = get_time();
	while (now - start < time_to_do)
	{
		if (should_stop(philo->shared_info))
			return (-1);
		now = get_time();
		//usleep(500);
	}
	return (0);
}

void	philo_print(t_info *info, int philo_num, char *message)
{
	int	now;

	now = get_time() - info->start_time;
	pthread_mutex_lock(&(info->print_lock));
	printf("%i %i %s\n", now, philo_num, message);
	pthread_mutex_unlock(&(info->print_lock));
}
