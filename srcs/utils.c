/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:47:54 by faventur          #+#    #+#             */
/*   Updated: 2022/05/24 10:44:46 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_diff(struct timeval *start, struct timeval *end)
{
	long	sec;
	long	usec;

	sec = end->tv_sec - start->tv_sec;
	usec = end->tv_usec - start->tv_usec;
	return (sec * 1000 + usec / 1000);
}

void	starting_blocks(long long time_to_eat)
{
	while (time_to_eat > 0)
	{
		usleep(50 * 1000);
		time_to_eat -= 50;
	}
}

int	time_goes_by(t_sophist philo, long standard)
{
	if (philo.last_meal > standard)
		return (1);
	return (0);
}

long	whats_the_time(void)
{
	struct timeval	time;
	long			sec;
	long			usec;

	gettimeofday(&time, NULL);
	sec = time.tv_sec;
	usec = time.tv_usec;
	return (sec * 1000 + usec / 1000);
}
