/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   happy_hour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:12:27 by faventur          #+#    #+#             */
/*   Updated: 2022/05/27 12:20:55 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	solitude(t_sophist *philo)
{
	t_man	*rules;

	rules = philo->rules;
	take_notes(*philo, "has taken a fork");
	timecount(*philo, rules->time_to_die);
}

void	happy_hour(t_sophist *philo, t_man *rules)
{
	if (rules->tot == 1)
		solitude(philo);
	if ((rules->tot % 2 == 1 && philo->id == philo->rules->tot - 1)
		|| philo->id % 2 == 0)
	{
		gettimeofday(&philo->acting, NULL);
		timecount(*philo, rules->time_to_eat);
	}
}

void	*routine(void *philosophical_void)
{
	t_sophist	*philo;
	t_man		*rules;

	philo = (t_sophist *)philosophical_void;
	rules = philo->rules;
	happy_hour(philo, rules);
	while (!check_program_end(philo))
	{
		check_program_end(philo);
		eat(*philo);
		gettimeofday(&philo->last_meal, NULL);
		philo->meals_num++;
		think(*philo);
		check_program_end(philo);
		ft_sleep(*philo);
		check_program_end(philo);
	}
	return (NULL);
}
