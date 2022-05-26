/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:26:09 by faventur          #+#    #+#             */
/*   Updated: 2022/05/26 16:28:17 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The time_diff() function calculates how much time has elapsed
** between two points in time. It takes two timeval variables as
** parameters.
**
** The time_goes_by() function calculates the time elapsed from a
** point in time and returns 1 if its length in milliseconds is
** greater than the standard length passed as a parameter, 0
** otherwise.
**
** The length_diff() function calculates the difference between
** two long integers expressing a duration in time.
** 
** The get_the_time() functions transforms the values expressed as
** a timeval variable into a long int.
** 
** The timecount() function creates a duration in time.
*/

#include "philo.h"

long	time_diff(struct timeval *start, struct timeval *end)
{
	long	sec;
	long	usec;

	sec = end->tv_sec - start->tv_sec;
	usec = end->tv_usec - start->tv_usec;
	return (sec * 1000 + usec / 1000);
}

int	time_goes_by(struct timeval *time, long standard)
{
	struct timeval	now;
	long			sec;
	long			usec;

	gettimeofday(&now, NULL);
	sec = now.tv_sec - time->tv_sec;
	usec = now.tv_usec - time->tv_usec;
	if ((sec * 1000 + usec / 1000) > standard)
	{
		printf("%ld\n", time->tv_sec * 1000 + time->tv_usec / 1000);
		printf("%ld\n", now.tv_sec * 1000 + now.tv_usec / 1000);
		printf("%ld\n", sec * 1000 + usec / 1000);
		return (1);
	}
	return (0);
}

long	length_diff(long present, long past)
{
	return (present - past);
}

long	get_the_time(void)
{
	struct timeval	now;
	long			sec;
	long			usec;

	gettimeofday(&now, NULL);
	sec = now.tv_sec;
	usec = now.tv_usec;
	return (sec * 1000 + usec / 1000);
}

void	timecount(t_sophist philo, long duration)
{
	long	sec;
	long	usec;
	long	time;

	sec = philo.acting.tv_sec;
	usec = philo.acting.tv_usec;
	time = sec * 1000 + usec / 1000;
	while (length_diff(get_the_time(), time) < duration)
		usleep(50);
}
