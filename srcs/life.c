/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:43:31 by faventur          #+#    #+#             */
/*   Updated: 2022/05/24 15:34:46 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	the_end(t_man *ph)
{
	int	i;

	i = 0;
	while (i < ph->tot)
	{
		free(ph->pax[i]);
		if (pthread_join(ph->pax[i]->pt, (void *)&ph->pax[i]) != 0)
		{
			perror("The thread got lost");
			return ;
		}
		if (pthread_detach(ph->pax[i]->pt) != 0)
		{
			perror("Boh\n");
			return ;
		}
		pthread_mutex_destroy(&ph->forks[i]);
		printf("The thread finished its execution\n");
		free(ph->pax[i]);
		i++;
	}
	free(ph);
}

void	think(t_sophist philo, t_man rules, long long reflection_time)
{
	take_notes(philo, rules, "is studying religion");
	take_notes(philo, rules, "is feeling like an anarchist");
	take_notes(philo, rules, "is preparing a golpe");
	usleep(reflection_time * 1000);
}

void	take_notes(t_sophist philo, t_man rules, char *msg)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	pthread_mutex_lock(&rules.writing);
	printf("%ld %d %s\n", time_diff(&rules.start, &now), philo.id + 1, msg);
	pthread_mutex_unlock(&rules.writing);
}

void	eat(t_sophist philo, t_man rules, long long time_to_eat)
{
	(void)time_to_eat;
	pthread_mutex_lock(&rules.forks[philo.left_fork]);
	take_notes(philo, rules, "has taken a fork");
	pthread_mutex_lock(&rules.forks[philo.right_fork]);
	take_notes(philo, rules, "has taken a fork");
	pthread_mutex_lock(&rules.meal);
	take_notes(philo, rules, "is eating");
	timecount();
	gettimeofday(&philo.last_meal, NULL);
	philo.many_meals++;
	time_goes_by(&philo.last_meal, time_to_eat);
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
//	check_death(philo);
	if (philo->id == philo->rules->tot || philo->id % 2 == 0)
		starting_blocks(1500);
	while (42)
	{
		eat(*philo, *rules, 1500);
		think(*philo, *rules, 1500);
	}
	return (NULL);
}

/* remember the deadlocks! */