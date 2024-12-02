
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

typedef struct	s_info
{
	pthread_mutex_t	*forks;
	pthread_mutex_t print_lock;
	struct timeval	start_time;
	int	somebody_died;
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	minimum_eats;
}	t_info;

typedef struct s_philo
{
	int	philo_num;
	struct timeval	last_meal;
	pthread_t	thread;
	t_info	*shared_info;
}	t_philo;

void	error_message(char *message);
int	ft_atoi(const char *str);
unsigned long	milliseconds_since_start(t_philo *philo_info);

#endif