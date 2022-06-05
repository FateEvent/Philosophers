/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:43:31 by faventur          #+#    #+#             */
/*   Updated: 2022/05/28 11:05:58 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_notes(t_sophist philo, char *msg)
{
	t_man			rules;
	struct timeval	now;

	rules = *philo.rules;
	pthread_mutex_lock(&rules.writing);
	gettimeofday(&now, NULL);
	printf("%ld %d %s\n", time_diff(&rules.start, &now), philo.id + 1, msg);
	pthread_mutex_unlock(&rules.writing);
}

void	ft_sleep(t_sophist philo)
{
	take_notes(philo, "is sleeping");
	gettimeofday(&philo.acting, NULL);
	timecount(philo, philo.rules->time_to_sleep);
}

void	think(t_sophist philo)
{
	take_notes(philo, "is thinking");
}

void	eat(t_sophist philo)
{
	t_man	rules;

	rules = *philo.rules;
	pthread_mutex_lock(&rules.forks[philo.left_fork]);
	take_notes(philo, "has taken a fork");
	pthread_mutex_lock(&rules.forks[philo.right_fork]);
	take_notes(philo, "has taken a fork");
	pthread_mutex_lock(&rules.meal);
	take_notes(philo, "is eating");
	gettimeofday(&philo.acting, NULL);
	countdown(philo, rules.time_to_eat);
	pthread_mutex_unlock(&rules.forks[philo.left_fork]);
	pthread_mutex_unlock(&rules.forks[philo.right_fork]);
	pthread_mutex_unlock(&rules.meal);
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
