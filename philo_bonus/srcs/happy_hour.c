/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   happy_hour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:12:27 by faventur          #+#    #+#             */
/*   Updated: 2022/06/15 12:03:13 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	solitude(t_data *philo)
{
	t_man	*rules;

	rules = philo->rules;
	take_notes(*philo, "has taken a fork");
	timecount(*philo, rules->time_to_die);
}

void	*happy_hour(t_data *philo)
{
	t_man	*rules;

	printf("ici!\n");
	rules = philo->rules;
	while (!check_program_end(philo))
	{
		eat(*philo);
		check_deaths(rules);
		gettimeofday(&philo->last_meal, NULL);
		philo->meals_num++;
		think(*philo);
		check_deaths(rules);
		ft_sleep(*philo);
		check_deaths(rules);
	}
	return (NULL);
}
