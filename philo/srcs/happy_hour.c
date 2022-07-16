/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   happy_hour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:12:27 by faventur          #+#    #+#             */
/*   Updated: 2022/07/16 14:20:00 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	solitude(t_sophist *philo)
{
	t_man	*rules;

	rules = philo->rules;
	take_notes(philo, "has taken a fork");
	countdown(philo, rules->time_to_die);
}

void	happy_hour(t_sophist *philo, t_man *rules)
{
	if (rules->tot == 1)
	{
		gettimeofday(&philo->acting, NULL);
		solitude(philo);
		return ;
	}
	if ((rules->tot % 2 == 1 && philo->id == philo->rules->tot - 1)
		|| philo->id % 2 == 0)
	{
		gettimeofday(&philo->acting, NULL);
		timecount(philo, rules->time_to_eat);
	}
}
