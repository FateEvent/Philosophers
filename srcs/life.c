/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:43:31 by faventur          #+#    #+#             */
/*   Updated: 2022/05/26 17:05:08 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	the_end(t_man *rules)
{
	int	i;

	i = 0;
	while (i < rules->tot)
	{
		free(rules->pax[i]);
		if (pthread_join(rules->pax[i]->pt, (void *)&rules->pax[i]) != 0)
		{
			perror("The thread got lost");
			return ;
		}
		if (pthread_detach(rules->pax[i]->pt) != 0)
		{
			perror("Boh\n");
			return ;
		}
		pthread_mutex_destroy(&rules->forks[i]);
		printf("The thread finished its execution\n");
		free(rules->pax[i]);
		i++;
	}
	free(rules);
}

void	take_notes(t_sophist philo, char *msg)
{
	t_man			rules;
	struct timeval	now;

	rules = *philo.rules;
	gettimeofday(&now, NULL);
	pthread_mutex_lock(&rules.writing);
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
	timecount(philo, rules.time_to_eat);
	gettimeofday(&philo.last_meal, NULL);
//	printf("last meal de %d %ld\n", philo.id, philo.last_meal.tv_sec * 1000 + philo.last_meal.tv_usec / 1000);
	philo.meals_num++;
	printf("philo %d happy meal %ld\n", philo.id, philo.meals_num);
	pthread_mutex_unlock(&rules.forks[philo.left_fork]);
	pthread_mutex_unlock(&rules.forks[philo.right_fork]);
	pthread_mutex_unlock(&rules.meal);
}
/* remember the deadlocks! */