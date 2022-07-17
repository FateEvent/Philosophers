/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:39:52 by faventur          #+#    #+#             */
/*   Updated: 2022/07/17 13:44:18 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*wait_pid_end(void *rules)
{
	t_man	*ptr;
	int		i;

	i = 0;
	ptr = rules;
	while (i < ptr->tot)
	{
		waitpid(ptr->pid[i], NULL, 0);
		++i;
	}
	return (NULL);
}

void	the_end(t_man *rules)
{
	int	i;

	i = 0;
	while (i < rules->tot)
	{
		kill(rules->pid[i], SIGINT);
		i++;
	}
	waitpid(-1, NULL, 0);
	sem_close(rules->forks);
	sem_close(rules->check);
	sem_close(rules->writing);
	free(rules->pax);
	rules->pax = NULL;
	free(rules);
	rules = NULL;
	exit(0);
}

int	death_note(t_sophist *philo)
{
	struct timeval	now;
	int				ret;

	ret = 0;
	gettimeofday(&now, NULL);
	if (ft_get_time(philo) - philo->last_meal >= philo->rules->time_to_die)
	{
		sem_wait(philo->rules->writing);
		philo->dead = 1;
		printf("%lld %d %s\n", ft_get_time(philo),
			philo->id + 1, "died");
		sem_post(philo->rules->check);
		return (1);
	}
	return (0);
}
