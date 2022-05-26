/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:47:54 by faventur          #+#    #+#             */
/*   Updated: 2022/05/26 17:01:36 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		ft_puterror("Error: the number of arguments is incorrect.");
		return (0);
	}
	return (1);
}

void	check_death(t_sophist *philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (philo->meals_num > 0)
	{
		if (time_diff(&philo->last_meal, &now) > philo->rules->time_to_die)
		{
			philo->dead = 1;
			take_notes(*philo, "has died\n");
			printf("from last meal m_num %ld code num %d\n", philo->meals_num, philo->id);
			printf("from last meal %ld\n", now.tv_sec * 1000 + now.tv_usec / 1000 - philo->last_meal.tv_sec * 1000 + philo->last_meal.tv_usec / 1000);
			exit(0);
		}
	}
	else if (philo->meals_num == 0)
	{
		if (time_diff(&philo->rules->start, &now) > philo->rules->time_to_die)
		{
			philo->dead = 1;
			take_notes(*philo, "has died\n");
			printf("from start m_num %ld code num %d\n", philo->meals_num, philo->id);
			printf("from start %ld\n", now.tv_sec * 1000 + now.tv_usec / 1000 - philo->rules->start.tv_sec * 1000 + philo->rules->start.tv_usec / 1000);
			exit(0);
		}
	}
}

void	check_program_end(t_sophist	*ph)
{
	int	i;

	i = 0;
	while (i <= ph->rules->tot)
	{
		if (ph->rules->pax[i]->dead == 1)
			the_end(ph->rules);
		i++;
		if (i == ph->rules->tot)
			i = 0;
	}
}
