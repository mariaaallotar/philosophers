/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:45:04 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/09 16:27:21 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutextes(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		pthread_mutex_destroy(&(info->forks[i]));
		i++;
	}
}

pthread_mutex_t	*create_fork_array(int num_of_philos)
{
	pthread_mutex_t	*forks;
	int	i;

	forks = malloc(num_of_philos * sizeof(pthread_mutex_t));
	if (forks == NULL)
	{
		error_message("Malloc failed to allocate memory for forks array, \
			exiting the program\n");
		return (NULL);
	}
	i = 0;
	while (i < num_of_philos)
	{
		if (pthread_mutex_init(&(forks[i]), NULL) != 0)
		{
			error_message("Mutex initialization failed, exiting the program\n");
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}
