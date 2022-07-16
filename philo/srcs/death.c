/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:39:52 by faventur          #+#    #+#             */
/*   Updated: 2022/07/16 16:17:24 by faventur         ###   ########.fr       */
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

int	death_note(t_sophist *philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (time_diff(&philo->last_meal, &now) > philo->rules->time_to_die)
	{
		philo->dead = 1;
		philo->rules->deaths = 1;
		take_notes(philo, "died");
		pthread_mutex_unlock(&philo->rules->check);
		return (1);
	}
	return (0);
}
