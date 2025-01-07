/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:26:32 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/18 10:30:03 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_philo **philo_pointers, t_info *info)
{
	int		i;
	int		*ret;
	t_philo	*philos;

	i = 0;
	while (i < info->num_of_philos)
	{
		philos = *philo_pointers++;
		if (pthread_join(philos->thread, (void **)&ret) != 0)
		{
			error_message("Failed to join thread, "
				"unexpected beahviour expected\n");
		}
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
		if (pthread_detach(philos->thread) != 0)
		{
			error_message("Failed to detach thread, "
				"unexpected beahviour expected\n");
		}
		i--;
	}
}

t_philo	*init_philo_data(t_info *info, int i, t_philo **philos)
{
	t_philo	*philo;
	int		left_fork;
	int		right_fork;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
	{
		free_and_destroy(info, info->forks, &(info->lock), philos);
		error_message("Failed to malloc a philo, exiting the program\n");
		return (NULL);
	}
	philo->shared_info = info;
	philo->philo_num = i + 1;
	philos[i] = philo;
	left_fork = philo->philo_num - 1;
	if (philo->philo_num == philo->shared_info->num_of_philos)
		right_fork = 0;
	else
		right_fork = philo->philo_num;
	philo->left_fork = &(info->forks[left_fork]);
	philo->right_fork = &(info->forks[right_fork]);
	info->start_time = get_time();
	philo->last_meal = info->start_time;
	return (philo);
}

int	start_philo(t_info *info, int i, t_philo **philos)
{
	t_philo	*philo;

	philo = init_philo_data(info, i, philos);
	if (philo == NULL)
		return (-1);
	if (pthread_create(&(philo->thread), NULL, philo_start, philo) != 0)
	{
		detach_threads(philos, i);
		free_and_destroy(info, info->forks, &(info->lock), philos);
		error_message("Failed to create thread, exiting the program\n");
		return (-1);
	}
	return (1);
}
