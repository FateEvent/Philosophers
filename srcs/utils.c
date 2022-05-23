/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:47:54 by faventur          #+#    #+#             */
/*   Updated: 2022/05/23 20:31:48 by faventur         ###   ########.fr       */
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

void	starting_blocks(long long eating_time)
{
	while (eating_time > 0)
	{
		usleep(50 * 1000);
		eating_time -= 50;
	}
}

int	time_goes_by(t_man *rules, long standard)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (time_diff(&rules->start, &time) > standard)
		return (1);
	return (0);
}
