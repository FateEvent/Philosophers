/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:43:31 by faventur          #+#    #+#             */
/*   Updated: 2022/07/17 13:54:02 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_notes(t_sophist *philo, char *msg)
{
	t_man	*rules;

	rules = philo->rules;
	sem_wait(rules->writing);
	printf("%lld %d %s\n", ft_get_time(philo), philo->id + 1, msg);
	sem_post(rules->writing);
}

void	ft_sleep(t_sophist *philo)
{
	if (death_note(philo))
		return ;
	take_notes(philo, "is sleeping");
	gettimeofday(&philo->acting, NULL);
	countdown(philo, philo->rules->time_to_sleep);
	if (death_note(philo))
		return ;
}

void	think(t_sophist *philo)
{
	if (death_note(philo))
		return ;
	take_notes(philo, "is thinking");
	if (death_note(philo))
		return ;
}

void	eat(t_sophist *philo)
{
	t_man	rules;

	rules = *philo->rules;
	if (death_note(philo))
		return ;
	sem_wait(rules.forks);
	take_notes(philo, "has taken a fork");
	if (death_note(philo))
		return ;
	sem_wait(rules.forks);
	take_notes(philo, "has taken a fork");
	philo->last_meal = ft_get_time(philo);
	take_notes(philo, "is eating");
	gettimeofday(&philo->acting, NULL);
	countdown(philo, rules.time_to_eat);
	sem_post(rules.forks);
	sem_post(rules.forks);
}
