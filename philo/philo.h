/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:31:08 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/16 15:26:53 by maheleni         ###   ########.fr       */
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
	pthread_mutex_t lock;
	pthread_mutex_t print_lock;
	size_t	start_time;
	int	somebody_died;
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	minimum_eats;
	int	philos_finished;
	//int	start;
}	t_info;

typedef struct s_philo
{
	int	philo_num;
	size_t	last_meal;
	pthread_t	thread;
	t_info	*shared_info;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo; 


void	destroy_forks(pthread_mutex_t *forks, int i);
void	free_and_destroy(t_info *info, pthread_mutex_t *forks, pthread_mutex_t
	*lock, t_philo **philos);
int	ft_atoi(const char *str);
void	error_message(char *message);
size_t	ft_strlen(const char *s);
void    *philo_start(void *args);
int	monitor_philos(t_info *info, t_philo **philos);
int	should_stop(t_info *shared_info);
int	start_philo(t_info *info, int i, t_philo **philos);
pthread_mutex_t	*create_fork_array(int num_of_philos);
void	join_threads(t_philo **philo_pointers, t_info *info);
void	philo_print(t_info *info, int philo_num, char *message);
int	dynamic_wait(t_philo *philo, int time_to_do);
void    philo_life(t_philo *philo);
int philo_eat(t_philo *philo);
int	create_data_and_print_mutexes(t_info *info);
size_t    get_time(void);

#endif