/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:26:32 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/10 16:04:51 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_philo **philo_pointers, t_info *info)
{
	int	i;
	int	*ret;
	t_philo	*philos;

	i = 0;
	while (i < info->num_of_philos)
	{
		philos = *philo_pointers++;
		pthread_join(philos->thread, (void **)&ret);
		if (errno)
			perror(NULL);
		i++;
	}
}

void	detach_threads(t_philo **philo_pointers, int i)
{
	t_philo	*philos;

	i--;
	while (i >= 0)
	{
		philos = *philo_pointers++;
		pthread_detach(philos->thread);
		i--;
	}
}

int	create_thread(t_info *info, int i, t_philo **philos)
{
	t_philo	*philo;
	int		left_fork;
	int		right_fork;

    philo = malloc(sizeof(t_philo));
	philo->shared_info = info;
	gettimeofday(&(philo->last_meal), NULL);
	philo->philo_num = i + 1;
	philos[i] = philo;
	left_fork = philo->philo_num - 1;
	if (philo->philo_num == philo->shared_info->num_of_philos)
		right_fork = 0;
	else
		right_fork = philo->philo_num;
	philo->left_fork = &(info->forks[left_fork]);
	philo->right_fork = &(info->forks[right_fork]);
	if (pthread_create(&(philo->thread), NULL, philo_life, philo) != 0)
	{
		info->somebody_died = -1;		//remember this
		detach_threads(philos, i);
		destroy_mutextes(info);
		free(info->forks);
		free(philos);
		error_message("Failed to create thread, exiting the program\n");
		return (-1);
	}
	return (1);
}
