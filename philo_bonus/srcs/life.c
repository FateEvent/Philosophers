/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:43:31 by faventur          #+#    #+#             */
/*   Updated: 2022/06/15 11:38:16 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_notes(t_data philo, char *msg)
{
	t_man			rules;
	struct timeval	now;

	rules = *philo.rules;
	sem_wait(rules.writing);
	gettimeofday(&now, NULL);
	printf("%ld %d %s\n", time_diff(&rules.start, &now), philo.id + 1, msg);
	sem_post(rules.writing);
}

void	ft_sleep(t_data philo)
{
	take_notes(philo, "is sleeping");
	gettimeofday(&philo.acting, NULL);
	timecount(philo, philo.rules->time_to_sleep);
}

void	think(t_data philo)
{
	take_notes(philo, "is thinking");
}

void	eat(t_data philo)
{
	t_man	rules;

	sem_wait(rules.forks);
	rules = *philo.rules;
	take_notes(philo, "has taken a fork");
	take_notes(philo, "has taken a fork");
	take_notes(philo, "is eating");
	gettimeofday(&philo.acting, NULL);
	countdown(philo, rules.time_to_eat);
	sem_post(rules.forks);
}
