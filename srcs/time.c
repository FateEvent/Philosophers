/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:26:09 by faventur          #+#    #+#             */
/*   Updated: 2022/05/24 18:39:09 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The time_goes_by() function calculates the time elapsed from a
** point in time and returns 1 if its length in milliseconds is
** greater than the standard length passed as a parameter. ) will
** be returned in the opposite case.
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
		return (1);
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
	printf("time %ld\n", sec);
	usec = philo.acting.tv_usec;
	time = sec * 1000 + usec / 1000;
	while (length_diff(get_the_time(), time) < duration)
	{
//		printf("time %ld\n", get_the_time());
//		printf("time 2 %d\n", length_diff(time, get_the_time()) < duration);
		usleep(50);
	}
}
