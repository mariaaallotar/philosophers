/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_and_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:08:05 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/09 16:34:23 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_think(t_philo *philo)
{
	philo_print(philo->shared_info, philo->philo_num, "is thinking");
	if (milliseconds_since_start(philo->shared_info) < 5)
	{
		return (0);
	}
	return (dynamic_sleep(philo, philo->shared_info->time_to_think));
}

int	philo_sleep(t_philo *philo)
{
	philo_print(philo->shared_info, philo->philo_num, "is sleeping");
	return (dynamic_sleep(philo, philo->shared_info->time_to_sleep));
}
