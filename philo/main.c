
#include "philo.h"

int	create_thread(t_info *info, int i, t_philo *philos)
{
	t_philo		philo;
	pthread_t	thread;

	philo.shared_info = info;
	gettimeofday(&(philo.last_meal), NULL);
	philo.philo_num = i + 1;
	philo.thread = thread;
	philos[i] = philo;
	if (pthread_create(&(thread), NULL, philo_life, &philo) != 0)
	{
		detach_threads(philos, i);
		destroy_mutextes(info);
		free(info->forks);
		free(philos);
		error_message("Failed to create thread, exiting the program\n");
		return (-1);
	}
	return (1);
}

t_philo	*create_philos(t_info *info)
{
	int			i;
	t_philo		*philos;

	philos = malloc(info->num_of_philos * sizeof(t_philo));
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

int	init_info_struct(t_info *info, char *argv[])
{
	info->num_of_philos = ft_atoi(argv[1]);
	info->forks = create_fork_array(info->num_of_philos);
	if (info->forks == NULL)
		return (-1);
	if (pthread_mutex_init(&(info->print_lock), NULL) != 0)
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

int	main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philos;

	if (validate_args(argc, argv) == -1)
		return (0);
	if (init_info_struct(&info, argv) == -1)
		return (1);
	philos = create_philos(&info);
	if (philos == NULL)
		return (1);
}
