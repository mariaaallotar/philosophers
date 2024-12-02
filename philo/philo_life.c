/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:51:22 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/02 16:10:17 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *philo_life(void *args)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *) args;
	i = 0;
	while (1)
	{
		printf("%lu %i is thinking\n", milliseconds_since_start(philo->shared_info), philo->philo_num);
		if (i == 0 && philo->philo_num % 2 == 1)
			usleep (philo->shared_info->time_to_eat / 2);
		if (time_to_stop(philo))
			break ;
		if (philo_eat(philo) == -1)
			break ;
		i++;
		if (i == philo->shared_info->minimum_eats)
		{
			philo->shared_info->detach = 1;
			break ;
		}
		if (philo_sleep(philo) == -1)
			break ;
	}
	return (&(philo->shared_info->somebody_died));
}
