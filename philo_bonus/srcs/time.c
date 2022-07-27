/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:26:09 by faventur          #+#    #+#             */
/*   Updated: 2022/07/27 14:00:15 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_get_time() function takes the time and returns the
** duration (expressed as a long int) from the starting time
** of the program and the present time.
**
** The length_diff() function calculates the difference between
** two long integers expressing a duration in time.
** 
** The get_the_time() function takes the time and transforms the
** values expressed as a timeval variable into a long int.
** 
** The countdown() function creates a duration in time. It also
** checks if the philosopher dies, by calling the death_note
** function.
*/

#include "philo_bonus.h"

long long	ft_get_time(t_sophist *philo)
{
	long long	ms;

	gettimeofday(&philo->tva, NULL);
	ms = (philo->tva.tv_sec * (uint64_t)1000) + (philo->tva.tv_usec / 1000);
	return (ms - philo->runtime);
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

void	countdown(t_sophist *philo, long duration)
{
	long	sec;
	long	usec;
	long	time;

	sec = philo->acting.tv_sec;
	usec = philo->acting.tv_usec;
	time = sec * 1000 + usec / 1000;
	while (length_diff(get_the_time(), time) <= duration)
	{
		if (death_note(philo))
			return ;
		usleep(50);
		if (death_note(philo))
			return ;
	}
}
