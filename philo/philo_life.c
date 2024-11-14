
#include "philo.h"

int	died_of_hunger(t_philo *philo_info)
{
	struct timeval now;
	long	seconds;
	long	microseconds;
	long	milliseconds;

	gettimeofday(&now, NULL);
    seconds = now.tv_sec - philo_info->last_meal.tv_sec;
    microseconds = now.tv_usec - philo_info->last_meal.tv_usec;
    milliseconds = (seconds * 1000) + (microseconds / 1000);
	if (milliseconds > philo_info->time_to_die)
	{
		*(philo_info->somebody_died) = 1;
		printf("%ld %i died\n", get_time_elapsed(philo_info), philo_info->philo_num);
		return (1);
	}
	return (0);
}

int	time_to_stop(t_philo *philo_info)
{
	if (*(philo_info->somebody_died))
		return (1);
	if (died_of_hunger(philo_info))
		return (1);
	return (0);
}

int	philo_sleep(t_philo *philo_info)
{
	pthread_mutex_lock(&(philo_info->lock));
	printf("%ld %i is sleeping\n", get_time_elapsed(philo_info), philo_info->philo_num);
	pthread_mutex_unlock(&(philo_info->lock));
	usleep(philo_info->time_to_sleep * 1000);
	if (time_to_stop(philo_info))
		return (-1);
	return (1);
}

int	philo_take_fork(int index, t_philo *philo_info)
{
	pthread_mutex_lock(&(philo_info->lock));
	while (1)
	{
		if ((philo_info->forks)[index] == 0)
		{
			(philo_info->forks)[index] = 1;
			printf("%ld %i has taken a fork\n", get_time_elapsed(philo_info), philo_info->philo_num);
			break ;
		}
		if (time_to_stop(philo_info))
		{
			pthread_mutex_unlock(&(philo_info->lock));
			return (-1);
		}
	}
	pthread_mutex_unlock(&(philo_info->lock));
	if (time_to_stop(philo_info))
		return (-1);
	return (1);
}

int	philo_take_forks(t_philo *philo_info)
{
	if (philo_take_fork(philo_info->philo_num - 1, philo_info) == -1)
		return (-1);
	if (philo_info->philo_num == philo_info->num_of_philos)
	{
		if (philo_take_fork(0, philo_info) == -1)
			return (-1);
	}
	else
	{
		if (philo_take_fork(philo_info->philo_num, philo_info) == -1)
			return (-1);
	}
	return (1);
}

void	philo_release_forks(t_philo *philo_info)
{
	philo_info->forks[philo_info->philo_num - 1] = 0;
	if (philo_info->philo_num == philo_info->num_of_philos)
		philo_info->forks[0] = 0;
	else
		philo_info->forks[philo_info->philo_num] = 0;
}

int	philo_eat(t_philo *philo_info)
{
	if (philo_take_forks(philo_info) == -1)
		return (-1);
	printf("%ld %i is eating\n", get_time_elapsed(philo_info), philo_info->philo_num);
	gettimeofday(&(philo_info->last_meal), NULL);
	usleep(philo_info->time_to_eat * 1000);
	philo_release_forks(philo_info);
	return (1);
}

int	philo_think_eat(t_philo *philo_info)
{
	pthread_mutex_lock(&(philo_info->lock));
	printf("%ld %i is thinking\n", get_time_elapsed(philo_info), philo_info->philo_num);
	pthread_mutex_unlock(&(philo_info->lock));
	if (time_to_stop(philo_info))
		return (-1);
	if (philo_eat(philo_info) == -1)
		return (-1);
	return (1);
}

void	philo_test(t_philo *philo_info)
{
	printf("Philo %i is doing something\n", philo_info->philo_num);
	sleep(1);
}

void	*philo_life(void *args)
{
	t_philo	*philo_info;
	int	i;

	philo_info = (t_philo *) args;


	// pthread_mutex_lock(&(philo_info->lock));
	// printf("Philo %i saying hi at %ld!\n", ((t_philo *)philo_info)->philo_num, get_time_elapsed(philo_info));
	// printf("Somebody died: %i\n", *(philo_info->somebody_died));
	// if (philo_info->philo_num == 1)
	// 	*(philo_info->somebody_died) = 1;
	// pthread_mutex_unlock(&(philo_info->lock));



	if (philo_info->num_of_philos % 2 == 0 && philo_info->philo_num % 2 == 1)
	{
		philo_eat(philo_info);
		philo_sleep(philo_info);
	}
	else
	{

	}
	i = 0;
	while (1)
	{
		if (philo_think_eat(philo_info) == -1)
			break ;
		i++;
		if (i == philo_info->minimum_eats)
			break ;
		if (philo_sleep(philo_info) == -1)
			break ;
	}


	free(philo_info);
	return (NULL);
}