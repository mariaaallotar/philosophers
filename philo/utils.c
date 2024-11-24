
#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

void	error_message(char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	res;
	long	prev;

	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		prev = res;
		res = res * 10 + (*str - '0');
		if (prev != res / 10 && sign == -1)
			return (0);
		if (prev != res / 10 && sign == 1)
			return (-1);
		str++;
	}
	return ((int)(res * sign));
}

long	get_time_elapsed(t_philo *philo_info)
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
