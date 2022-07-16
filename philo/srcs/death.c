/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:39:52 by faventur          #+#    #+#             */
/*   Updated: 2022/07/16 14:28:00 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	the_end(t_man *rules)
{
	int	i;

	i = 0;
	while (i < rules->tot)
	{
		pthread_detach(rules->pax[i]->pt);
		pthread_mutex_destroy(&rules->forks[i]);
		free(rules->pax[i]);
		rules->pax[i] = NULL;
		i++;
	}
	pthread_mutex_destroy(&rules->check);
	free(rules->forks);
	rules->forks = NULL;
	free(rules);
	rules = NULL;
}

static int	death_note_pt2(struct timeval now, t_sophist *philo)
{
	if (philo->meals_num == 0)
	{
		if (time_diff(&philo->rules->start, &now) > philo->rules->time_to_die)
		{
			philo->dead = 1;
			philo->rules->deaths = 1;
			take_notes(philo, "died");
			pthread_mutex_unlock(&philo->rules->check);
			return (1);
		}
	}
	return (0);
}

int	death_note(t_sophist *philo)
{
	struct timeval	now;
	int				ret;

	ret = 0;
	gettimeofday(&now, NULL);
	if (philo->meals_num > 0)
	{
		if (time_diff(&philo->last_meal, &now) > philo->rules->time_to_die)
		{
			philo->dead = 1;
			philo->rules->deaths = 1;
			take_notes(philo, "died");
			pthread_mutex_unlock(&philo->rules->check);
			return (1);
		}
	}
	else if (philo->meals_num == 0)
		ret = death_note_pt2(now, philo);
	return (ret);
}
