/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:47:54 by faventur          #+#    #+#             */
/*   Updated: 2022/05/23 17:42:55 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_diff(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec) / 1000
		+ (end->tv_usec - start->tv_usec) * 1000);
}

void	starting_blocks(useconds_t eating_time)
{
	while (eating_time > 0)
	{
		usleep(50 * 1000);
		eating_time -= 50;
	}
}
