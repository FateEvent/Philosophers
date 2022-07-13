/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:47:54 by faventur          #+#    #+#             */
/*   Updated: 2022/07/13 19:36:15 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
int	check_deaths(t_man *rules)
{
	int	i;

	i = 0;
	while (i < rules->tot)
	{
		if (rules->pax[i]->dead > 0)
		{
			pthread_mutex_unlock(&rules->check);
			return (1);
		}
		i++;
		if (i == rules->tot - 1)
			i = 0;
	}
	return (0);
}
*/
int	check_deaths(t_sophist *philo)
{
	if (philo->dead > 0)
	{
		pthread_mutex_unlock(&philo->rules->check);
		return (1);
	}
	return (0);
}
/*
int	check_meals(t_man *rules)
{
	int	i;
	int	cmp;

	i = 0;
	if (rules->num_of_meals < 0)
		return (0);
	cmp = rules->num_of_meals;
	while (i < rules->tot)
	{
		if (rules->pax[i]->meals_num < cmp)
			return (0);
		i++;
	}
	rules->deaths = 1;
	pthread_mutex_unlock(&rules->check);
	return (1);
}
*/
int	check_meals(t_sophist *philo)
{
	int	cmp;

	if (philo->rules->num_of_meals < 0)
		return (0);
	cmp = philo->rules->num_of_meals;
	if (philo->meals_num < cmp)
		return (0);
	else
		philo->rules->deaths = 1;
	pthread_mutex_unlock(&philo->rules->check);
	return (1);
}

