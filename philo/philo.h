/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:31:08 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/09 16:50:38 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>

typedef struct	s_info
{
	pthread_mutex_t	*forks;
	pthread_mutex_t data_lock;
	pthread_mutex_t	print_lock;
	struct timeval	start_time;
	struct timeval	death_time;
	int	somebody_died;
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_think;
	int	minimum_eats;
	int	philos_finished;
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
unsigned long	milliseconds_since_start(t_info *info);
unsigned long   event_at_milliseconds(struct timeval event, t_info info);
void	detach_threads(t_philo **philo_pointers, int i);
void	join_threads(t_philo **philo_pointers, t_info *info);
void	destroy_mutextes(t_info *info);
pthread_mutex_t	*create_fork_array(int num_of_philos);
void    *philo_life(void *args);
int	philo_eat(t_philo *philo);
int	create_thread(t_info *info, int i, t_philo **philos);
int	died_of_hunger(t_philo *philo);
int	time_to_stop(t_philo *philo);
int	dynamic_sleep(t_philo *philo, int time_to_do);
void	philo_print(t_info *info, int philo_num, char *message);
int	philo_sleep(t_philo *philo);
int	philo_think(t_philo *philo);

#endif