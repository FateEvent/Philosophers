/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   happy_hour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:12:27 by faventur          #+#    #+#             */
/*   Updated: 2022/07/17 14:05:33 by faventur         ###   ########.fr       */
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
//	while (!death_note(philo) && !check_meals(philo->rules))
//	{
//		if (death_note(philo))
//			break ;
		eat(philo);
//		if (death_note(philo))
//			break ;
		think(philo);
//		if (death_note(philo))
//			break ;
		ft_sleep(philo);
//		if (death_note(philo))
//			break ;
//	}
	return (NULL);
}

void	philosopher_manage(t_sophist *philo)
{
	int	id;
	int	n;

	id = philo->id;
	philo->last_meal = ft_get_time(philo);
	n = philo->rules->num_of_meals;
	while (!philo->dead && !death_note(philo))
	{
		happy_hour(philo);
		if (n && n != -1)
		{
			--n;
			if (!n)
				exit (0);
		}
	}
}
