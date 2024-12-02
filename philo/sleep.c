/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:08:05 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/02 16:09:56 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_philo *philo)
{
	philo_print(philo->shared_info, philo->philo_num, "is sleeping");
	if (dynamic_sleep(philo, philo->shared_info->time_to_sleep) == -1)
		return (-1);
	if (time_to_stop(philo))
		return (-1);
	return (1);
}
