/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:43:31 by faventur          #+#    #+#             */
/*   Updated: 2022/05/23 18:53:23 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	the_end(t_man ph)
{
	int	i;

	i = 0;
	while (i < ph.tot)
	{
		free(ph.pax[i]);
		if (pthread_join(ph.pax[i]->pt, (void *)&ph.pax[i]) != 0)
		{
			perror("The thread got lost");
			return ;
		}
		if (pthread_detach(ph.pax[i]->pt) != 0)
		{
			perror("Boh\n");
			return ;
		}
		pthread_mutex_destroy(&ph.forks[i]);
		printf("The thread finished its execution\n");
		free(ph.pax[i]);
		i++;
	}
}

void	think(t_sophist philo, t_man rules, useconds_t reflection_time)
{
	take_notes(philo, rules, "is studying religion");
	take_notes(philo, rules, "is feeling like an anarchist");
	take_notes(philo, rules, "is preparing a golpe");
	usleep(reflection_time * 1000);
}

void	take_notes(t_sophist philo, t_man rules, char *msg)
{
	pthread_mutex_lock(&rules.writing);
	printf("%d %d %s\n", rules.start.tv_usec, philo.id, msg);
	pthread_mutex_unlock(&rules.writing);
}

void	eat(t_sophist philo, t_man rules, useconds_t eating_time)
{
	(void)eating_time;
	pthread_mutex_lock(&rules.forks[philo.left_fork]);
	take_notes(philo, rules, "has taken a fork");
	pthread_mutex_lock(&rules.forks[philo.right_fork]);
	take_notes(philo, rules, "has taken a fork");
	pthread_mutex_lock(&rules.meal);
	take_notes(philo, rules, "is eating");
	pthread_mutex_unlock(&rules.forks[philo.left_fork]);
	pthread_mutex_unlock(&rules.forks[philo.right_fork]);
	pthread_mutex_unlock(&rules.meal);
}

void	*routine(void *philosophical_void)
{
	t_sophist	*philo;
	t_man		rules;

	philo = (t_sophist *)philosophical_void;
	gettimeofday(&rules.start, NULL);
	if (philo->id % 2 == 0)
		starting_blocks(1500);
	while (42)
	{
		eat(*philo, rules, 1500);
		gettimeofday(&rules.end, NULL);
		think(*philo, rules, 1500);
		gettimeofday(&rules.end, NULL);
	}
	return (NULL);
}

/* remember the deadlocks! */