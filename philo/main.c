
#include "philo.h"

void	join_threads(pthread_t *threads, t_philo *philo_info)
{
	int	i;

	i = 0;
	while (i < philo_info->num_of_philos)
	{
		pthread_join(threads[i], NULL);
		//printf("Thread %i is joined\n", i + 1);
		i++;
	}
}

void	detach_threads(pthread_t *threads, int i)
{
	i--;
	while (i >= 0)
	{
		pthread_detach(threads[i]);
		i--;
	}
}

void	destroy_mutextes(t_philo *philo_info)
{
	int	i;

	i = 0;
	while (i < philo_info->num_of_philos)
	{
		pthread_mutex_destroy(&(philo_info->forks[i]));
		i++;
	}
}

int	create_thread(t_philo *philo_info_copy, int i, pthread_t *threads)
{
	t_philo	*philo_info;

	philo_info = malloc(sizeof(t_philo));
    if (!philo_info)
        return -1; // Handle allocation error
    *philo_info = *philo_info_copy; // Copy base info into new instance
    philo_info->philo_num = i + 1;
	if (pthread_create(&(threads[i]), NULL, philo_life, philo_info) != 0)
	{
		detach_threads(threads, i);
		destroy_mutextes(philo_info);
		free(philo_info->forks);
		error_message("Failed to create thread, exiting the program\n");
		return (-1);
	}
	return (1);
}

pthread_t	*create_threads(t_philo *philo_info)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(philo_info->num_of_philos * sizeof(pthread_t));
	if (threads == NULL)
	{
		error_message("Malloc failed to allocate memory for threads array, \
			exiting the program\n");
		destroy_mutextes(philo_info);
		free(philo_info->forks);
		return (NULL);
	}
	i = 0;
	while (i < philo_info->num_of_philos)
	{
		if (create_thread(philo_info, i, threads) == -1)
			return (NULL);
		i++;
	}
	return (threads);
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

int	init_philo_struct(t_philo *philo_info, char *argv[], int *somebody_died)
{
	philo_info->num_of_philos = ft_atoi(argv[1]);
	philo_info->forks = create_fork_array(philo_info->num_of_philos);
	if (philo_info->forks == NULL)
		return (-1);
	philo_info->time_to_die = ft_atoi(argv[2]);
	philo_info->time_to_eat = ft_atoi(argv[3]);
	philo_info->time_to_sleep = ft_atoi(argv[4]);
	philo_info->minimum_eats = -1;
	if (argv[5] != NULL)
		philo_info->minimum_eats = ft_atoi(argv[5]);
	philo_info->philo_num = 0;
	gettimeofday(&(philo_info->start_time), NULL);
	philo_info->last_meal = philo_info->start_time;
	*somebody_died = 0;
	philo_info->somebody_died = somebody_died;
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
	t_philo		philo_info;
	pthread_t	*threads;
	int			somebody_died;

	if (validate_args(argc, argv) == -1)
		return (0);
	if (init_philo_struct(&philo_info, argv, &somebody_died) == -1)
		return (1);
	threads = create_threads(&philo_info);
	if (threads == NULL)
		return (1);
	while (1)
	{
		if (*(philo_info.somebody_died))
		{
			join_threads(threads, &philo_info);
			break ;
		}
		usleep(5);
	}
	free(philo_info.forks);
	destroy_mutextes(&philo_info);
	return (0);
}