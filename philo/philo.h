
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_philo
{
	int	philo_num;
	struct timeval	last_meal;
	int	*forks;
	struct timeval	start_time;
	pthread_mutex_t lock;
	int	*somebody_died;
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_think;
	int	minimum_eats;
}	t_philo;

void	error_message(char *message);
int	ft_atoi(const char *str);
void	*philo_life(void *args);
long	get_time_elapsed(t_philo *philo_info);

#endif