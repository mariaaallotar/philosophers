/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:46:02 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/18 10:46:03 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_and_destroy(t_info *info, pthread_mutex_t *forks,
	pthread_mutex_t *lock, t_philo **philos)
{
	int	i;

	if (forks != NULL)
		destroy_forks(forks, info->num_of_philos - 1);
	free(forks);
	if (lock != NULL)
	{
		if (pthread_mutex_destroy(lock) != 0)
			error_message("Failed to destroy mutex\n");
	}
	if (philos != NULL)
	{
		i = 0;
		while (i < info->num_of_philos)
		{
			if (philos[i] != NULL)
				free(philos[i]);
			else if (philos[i] == NULL)
				break ;
			i++;
		}
		free(philos);
	}
}

int	init_info_struct(t_info *info, char *argv[])
{
	info->num_of_philos = ft_atoi(argv[1]);
	info->forks = create_fork_array(info->num_of_philos);
	if (info->forks == NULL)
		return (-1);
	if (create_data_and_print_mutexes(info) == -1)
		return (-1);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->minimum_eats = -1;
	if (argv[5] != NULL)
		info->minimum_eats = ft_atoi(argv[5]);
	info->philos_finished = 0;
	info->somebody_died = 0;
	info->start = 0;
	return (1);
}

int	validate_args(int argc, char *argv[])
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("\nUSAGE: This program must take 4 or 5 arguments,\nonly "
			"integers bigger than 0 and smaller than INT_MAX+1,\nthe maximum "
			"number of philos is 1000\nthe results "
			"for numbers outside of that range are undefined\n");
		printf("\nARGUMENTS:\nnumber_of_philosophers\ntime_to_die\ntime_to_eat\n"
			"time_to_sleep\n[number_of_times_each_philosopher_must_eat]\n\n");
		return (-1);
	}
	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_atoi(argv[i]) <= 0 || (i == 1 && ft_atoi(argv[i]) > 1000))
		{
			printf("Argument '%s' outside of accepted range\nExiting program\n",
				argv[i]);
			return (-1);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_philo	**philos;

	if (validate_args(argc, argv) == -1)
		return (0);
	if (init_info_struct(&info, argv) == -1)
		return (1);
	philos = create_philos(&info);
	if (philos == NULL)
		return (1);
	monitor_philos(&info, philos);
	if (info.somebody_died > 0)
		philo_print(&info, info.somebody_died, "died");
	free_and_destroy(&info, info.forks, &(info.lock), philos);
}
