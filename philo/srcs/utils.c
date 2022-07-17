/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:47:54 by faventur          #+#    #+#             */
/*   Updated: 2022/07/17 14:30:03 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_deaths(t_sophist *philo)
{
	if (philo->dead > 0)
	{
		philo->rules->deaths++;
		return (1);
	}
	return (0);
}

int	check_meals(t_sophist *philo)
{
	int	cmp;

	if (philo->rules->num_of_meals < 0)
		return (0);
	cmp = philo->rules->num_of_meals;
	if (philo->meals_num <= cmp)
		return (0);
	else
		philo->rules->deaths = 1;
	return (1);
}

void	check_end(t_man *rules)
{
	struct timeval	now;
	int				i;

	i = 0;
	while (!rules->deaths)
	{
		gettimeofday(&now, NULL);
		if (time_diff(&rules->pax[i]->last_meal, &now)
			> rules->time_to_die)
			death_note(rules->pax[i]);
		if (i == rules->tot - 1)
			i = -1;
		i++;
	}
}
