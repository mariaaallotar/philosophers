/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:26:47 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/05 16:19:00 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**create_philos(t_info *info)
{
	int			i;
	t_philo		**philos;

	philos = malloc(info->num_of_philos * sizeof(t_philo *));
	if (philos == NULL)
	{
		error_message("Malloc failed to allocate memory for philo array, \
			exiting the program\n");
		destroy_mutextes(info);
		free(info->forks);
		return (NULL);
	}
	i = 0;
	while (i < info->num_of_philos)
	{
		if (create_thread(info, i, philos) == -1)
			return (NULL);
		i++;
	}
	return (philos);
}

int	init_info_struct(t_info *info, char *argv[])
{
	info->num_of_philos = ft_atoi(argv[1]);
	info->forks = create_fork_array(info->num_of_philos);
	if (info->forks == NULL)
		return (-1);
	if (pthread_mutex_init(&(info->lock), NULL) != 0)
	{
		free(info->forks);
		error_message("Mutex initialization failed, exiting the program\n");
		return (-1);
	}
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->minimum_eats = -1;
	if (argv[5] != NULL)
		info->minimum_eats = ft_atoi(argv[5]);
	info->philos_finished = 0;
	gettimeofday(&(info->start_time), NULL);
	info->somebody_died = 0;
	return (1);
}

int	validate_args(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("\nUSAGE: This program must take 4 or 5 arguments,\nall "
			"integers bigger than 0 and smaller than INT_MAX+1,\nthe results "
			"for numbers outside of that range are undefined\n");
		printf("\nARGUMENTS:\nnumber_of_philosophers\ntime_to_die\ntime_to_eat\n"
			"time_to_sleep\n[number_of_times_each_philosopher_must_eat]\n\n");
		return (-1);
	}
	argv++;
	while (*argv != NULL)
	{
		if (ft_atoi(*argv) <= 0)
		{
			printf("Argument '%s' outside of accepted range\nExiting program\n",
				*argv);
			return (-1);
		}
		argv++;
	}
	return (1);
}

// void	monitor_philos(t_info *info, t_philo *philos)
// {
// 	//is this function at all needed

// 	// int	i;

// 	while (1)
// 	{
// 		// i = 0;
// 		// while (i < info->num_of_philos)
// 		// {
// 		// 	// printf("Looking if %i died of hunger\n", philos[i].philo_num);
// 		// 	if (died_of_hunger(&(philos[i])))
// 		// 		break ;
// 		// 	i++;
// 		// }
// 		// printf("STATUS: %i %p\n", info->somebody_died, &(info->somebody_died));
// 		if (info->somebody_died)
// 		{
// 			detach_threads(philos, info->num_of_philos);
// 			printf("%lu %i died\n", milliseconds_since_start(info), info->somebody_died);
// 			break ;
// 		}
// 		if (info->detach)
// 		{
// 			join_threads(philos, info);
// 			break ;
// 		}
// 		usleep(5000);
// 	}
// }

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
	join_threads(philos, &info);
	// if (info.somebody_died > 0)
	// 	printf("%lu %i died\n", milliseconds_since_start(&info), info.somebody_died);
	destroy_mutextes(&info);
	free(info.forks);
	free(philos);
	return (0);
}
