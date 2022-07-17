/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   happy_hour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:12:27 by faventur          #+#    #+#             */
/*   Updated: 2022/07/17 12:51:54 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	solitude(t_sophist *philo)
{
	t_man	*rules;

	rules = philo->rules;
	take_notes(philo, "has taken a fork");
	countdown(philo, rules->time_to_die);
}

void	*happy_hour(t_sophist *philo)
{
	t_man	*rules;

	rules = philo->rules;
	while (ft_get_time(philo) - philo->last_meal <= philo->rules->time_to_die
		&& !check_meals(philo->rules))
	{
		eat(philo);
		if (death_note(philo))
			break ;
		philo->meals_num++;
		think(philo);
		if (death_note(philo))
			break ;
		ft_sleep(philo);
		if (death_note(philo))
			break ;
	}
	return (NULL);
}
