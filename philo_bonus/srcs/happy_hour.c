/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   happy_hour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:12:27 by faventur          #+#    #+#             */
/*   Updated: 2022/06/05 18:17:07 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	solitude(t_sophist *philo)
{
	t_man	*rules;

	rules = philo->rules;
	take_notes(*philo, "has taken a fork");
	timecount(*philo, rules->time_to_die);
}

void	*happy_hour(t_sophist *philo)
{
	t_man		*rules;

	rules = philo->rules;
	while (!check_program_end(philo))
	{
		eat(*philo);
		if (rules->deaths)
			break ;
		gettimeofday(&philo->last_meal, NULL);
		philo->meals_num++;
		think(*philo);
		if (rules->deaths)
			break ;
		ft_sleep(*philo);
		if (rules->deaths)
			break ;
	}
	return (NULL);
}
