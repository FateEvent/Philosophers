/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:39:52 by faventur          #+#    #+#             */
/*   Updated: 2022/06/15 10:59:50 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	the_game_ends(t_man *rules)
{
	int	i;

	i = 0;
	while (i < rules->tot)
	{
		kill(rules->data->pid[i], SIGKILL);
		++i;
	}
	sem_close(rules->forks);
	sem_close(rules->check);
	free(rules->data->pid);
	free(rules->data);
}

static int	death_note_pt2(struct timeval now, t_data *philo)
{
	if (philo->meals_num == 0)
	{
		if (time_diff(&philo->rules->start, &now) > philo->rules->time_to_die)
		{
			printf("pappa 2");
			philo->dead = 1;
			take_notes(*philo, "has died");
			sem_post(philo->rules->check);
			the_game_ends(philo->rules);
			return (1);
		}
	}
	return (0);
}

int	death_note(t_data *philo)
{
	struct timeval	now;
	int				ret;

	ret = 0;
	gettimeofday(&now, NULL);
	sem_wait(philo->rules->check);
	if (philo->meals_num > 0)
	{
//		printf("%ld\n", time_diff(&philo->last_meal, &now));
		if (time_diff(&philo->last_meal, &now) > philo->rules->time_to_die)
		{
			philo->dead = 1;
			take_notes(*philo, "has died");
			sem_post(philo->rules->check);
			the_game_ends(philo->rules);
			return (1);
		}
	}
	else if (philo->meals_num == 0)
		ret = death_note_pt2(now, philo);
	return (ret);
}
