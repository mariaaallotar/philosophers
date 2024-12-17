/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:45:04 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/17 15:19:05 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(pthread_mutex_t *forks, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&(forks[i]));
		i--;
	}
}

pthread_mutex_t	*create_fork_array(int num_of_philos)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(num_of_philos * sizeof(pthread_mutex_t));
	if (forks == NULL)
	{
		error_message("Malloc failed to allocate memory for forks array," \
			" exiting the program\n");
		return (NULL);
	}
	i = 0;
	while (i < num_of_philos)
	{
		if (pthread_mutex_init(&(forks[i]), NULL) != 0)
		{
			error_message("Mutex initialization failed, exiting the program\n");
			destroy_forks(forks, i - 1);
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

int	create_data_and_print_mutexes(t_info *info)
{
	if (pthread_mutex_init(&(info->lock), NULL) != 0)
	{
		destroy_forks(info->forks, info->num_of_philos - 1);
		free(info->forks);
		error_message("Mutex initialization failed, exiting the program\n");
		return (-1);
	}
	if (pthread_mutex_init(&(info->print_lock), NULL) != 0)
	{
		pthread_mutex_destroy(&(info->lock));
		destroy_forks(info->forks, info->num_of_philos - 1);
		free(info->forks);
		error_message("Mutex initialization failed, exiting the program\n");
		return (-1);
	}
	return (1);
}
