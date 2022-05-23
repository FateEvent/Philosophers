/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:47:54 by faventur          #+#    #+#             */
/*   Updated: 2022/05/23 18:20:28 by faventur         ###   ########.fr       */
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

void	time_goes_by(useconds_t current_time, useconds_t count_to_add)
{
	current_time = (current_time + count_to_add) * 1000;
}
