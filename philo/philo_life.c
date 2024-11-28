
#include "philo.h"

int	get_current_time_milliseconds(t_philo *philo_info)
{
	struct timeval now;
	long	seconds;
	long	microseconds;
	long	milliseconds;

	gettimeofday(&now, NULL);
    seconds = now.tv_sec - philo_info->start_time.tv_sec;
    microseconds = now.tv_usec - philo_info->start_time.tv_usec;
    milliseconds = (seconds * 1000) + (microseconds / 1000);
	return (milliseconds);
}

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
		*(philo_info->somebody_died) = philo_info->philo_num;
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

int	dynamic_sleep(t_philo *philo_info)
{
	size_t			start;

	start = get_current_time_milliseconds(philo_info);
	while ((get_current_time_milliseconds(philo_info) - start)
		< (unsigned long) philo_info->time_to_sleep)
	{
		usleep(500);
		if (time_to_stop(philo_info))
			return (-1);
	}
	return (0);
}

int	philo_sleep(t_philo *philo_info)
{
	printf("%ld %i is sleeping\n", get_time_elapsed(philo_info), philo_info->philo_num);
	if (dynamic_sleep(philo_info) == -1)
		return (-1);
	if (time_to_stop(philo_info))
		return (-1);
	return (1);
}

int	philo_take_forks(t_philo *philo_info)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo_info->philo_num - 1;
	if (philo_info->philo_num == philo_info->num_of_philos)
		right_fork = 0;
	else
		right_fork = philo_info->philo_num;
	pthread_mutex_lock(&(philo_info->forks[left_fork]));
	printf("%ld %i has taken a fork\n", get_time_elapsed(philo_info), philo_info->philo_num);
	if (time_to_stop(philo_info))
		return (-1);
	pthread_mutex_lock(&(philo_info->forks[right_fork]));
	printf("%ld %i has taken a fork\n", get_time_elapsed(philo_info), philo_info->philo_num);
	if (time_to_stop(philo_info))
		return (-1);
	return (1);
}

void	philo_release_forks(t_philo *philo_info)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo_info->philo_num - 1;
	pthread_mutex_unlock(&(philo_info->forks[left_fork]));
	if (philo_info->philo_num == philo_info->num_of_philos)
		right_fork = 0;
	else
		right_fork = philo_info->philo_num;
	pthread_mutex_unlock(&(philo_info->forks[right_fork]));
	//printf("%ld %i has released forks\n", get_time_elapsed(philo_info), philo_info->philo_num);
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

// void	philo_test(t_philo *philo_info)
// {
// 	printf("Philo %i is doing something\n", philo_info->philo_num);
// 	sleep(1);
// }

void	*philo_life(void *args)
{
	t_philo	*philo_info;
	int	i;

	philo_info = (t_philo *) args;
	i = 0;
	if (philo_info->philo_num % 2 == 1 && philo_info->philo_num != philo_info->num_of_philos)
	{
		if (philo_eat(philo_info) == -1)
		{
			free(philo_info);
			return (NULL);
		}
		if (philo_sleep(philo_info) == -1)
		{
			free(philo_info);
			return (NULL);
		}
		i++;
	}
	while (1)
	{
		printf("%ld %i is thinking\n", get_time_elapsed(philo_info), philo_info->philo_num);
		if (i == 0)
			usleep (philo_info->time_to_eat / 2);
		if (time_to_stop(philo_info))
			break ;
		if (philo_eat(philo_info) == -1)
			break ;
		i++;
		if (i == philo_info->minimum_eats)
			break ;
		if (philo_sleep(philo_info) == -1)
			break ;
	}
	if (philo_info->philo_num == *(philo_info->somebody_died))
		printf("%ld %i died\n", get_time_elapsed(philo_info), philo_info->philo_num);
	free(philo_info);
	return (NULL);
}