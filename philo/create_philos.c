/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:36:27 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/18 10:56:33 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_philos(t_info *info, t_philo **philos)
{
	int	i;
	int	num_of_philos;

	pthread_mutex_lock(&(info->lock));
	num_of_philos = info->num_of_philos;
	pthread_mutex_unlock(&(info->lock));
	i = 0;
	while (i < num_of_philos)
	{
		if (start_philo(info, i, philos) == -1)
			return (-1);
		printf("0 %i is thinking\n", i + 1);
		i++;
	}
	pthread_mutex_lock(&(info->lock));
	info->start_time = get_time();
	info->start = 1;
	pthread_mutex_unlock(&(info->lock));
	return (0);
}

t_philo	**create_philos(t_info *info)
{
	t_philo		**philos;

	philos = malloc(info->num_of_philos * sizeof(t_philo *));
	if (philos == NULL)
	{
		free_and_destroy(info, info->forks, &(info->lock), NULL);
		error_message("Malloc failed to allocate memory for philo array," \
			" exiting the program\n");
		return (NULL);
	}
	memset(philos, 0, sizeof(*philos) * info->num_of_philos);
	if (start_philos(info, philos) == -1)
		return (NULL);
	return (philos);
}
