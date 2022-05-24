/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:47:54 by faventur          #+#    #+#             */
/*   Updated: 2022/05/24 15:27:35 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	starting_blocks(long long time_to_eat)
{
	while (time_to_eat > 0)
	{
		usleep(50 * 1000);
		time_to_eat -= 50;
	}
}

void	check_death(t_sophist *philo)
{
	if (philo->many_meals > 0)
	{
		if (!time_goes_by(&philo->last_meal, philo->rules->time_to_eat))
			the_end(philo->rules);
	}
	else
	{
		if (!time_goes_by(&philo->rules->start, philo->rules->time_to_eat))
			the_end(philo->rules);
	}
}
