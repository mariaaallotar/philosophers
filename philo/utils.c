/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:27:10 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/10 13:37:36 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (*str != '\0')
		return (-1);
	return ((int)(res * sign));
}

unsigned long	milliseconds_since_start(t_info *info)
{
	struct timeval now;
	unsigned long	seconds;
	unsigned long	microseconds;
	unsigned long	milliseconds;

	gettimeofday(&now, NULL);
    seconds = now.tv_sec - info->start_time.tv_sec;
    if (now.tv_usec < info->start_time.tv_usec)
    {
		seconds--;
        microseconds = (now.tv_usec + 1000000) - info->start_time.tv_usec;
    }
    else
    {
        microseconds = now.tv_usec - info->start_time.tv_usec;
    }
    milliseconds = (seconds * 1000) + (microseconds / 1000);
	return (milliseconds);
}
