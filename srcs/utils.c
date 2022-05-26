/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:47:54 by faventur          #+#    #+#             */
/*   Updated: 2022/05/26 19:38:46 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		ft_puterror("Error: the number of arguments is incorrect.");
		return (0);
	}
	return (1);
}

int	check_meals(t_man *rules)
{
	int	i;
	int	cmp;

	i = 1;
	cmp = rules->pax[0]->meals_num;
	while (i < rules->tot)
	{
		if (rules->pax[i]->meals_num != cmp)
			return (0);
		i++;
	}
	if (rules->num_of_meals != -1)
		rules->num_of_meals--;
	return (1);
}

int	check_death(t_sophist *philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (philo->meals_num > 0)
	{
		if (time_diff(&philo->last_meal, &now) > philo->rules->time_to_die)
		{
			philo->dead = 1;
			take_notes(*philo, "has died\n");
			printf("from last meal m_num %ld code num %d\n", philo->meals_num, philo->id + 1);
			printf("from last meal %ld\n", now.tv_sec * 1000 + now.tv_usec / 1000 - philo->last_meal.tv_sec * 1000 + philo->last_meal.tv_usec / 1000);
			exit(1);
		}
	}
	else if (philo->meals_num == 0)
	{
		if (time_diff(&philo->rules->start, &now) > philo->rules->time_to_die)
		{
			philo->dead = 1;
			take_notes(*philo, "has died\n");
			printf("from start m_num %ld code num %d\n", philo->meals_num, philo->id + 1);
			printf("from start %ld\n", now.tv_sec * 1000 + now.tv_usec / 1000 - philo->rules->start.tv_sec * 1000 + philo->rules->start.tv_usec / 1000);
			exit(1);
		}
	}
	return (0);
}

void	check_program_end(t_sophist	*ph)
{
	int	i;

	i = 0;
	if (ph->rules->num_of_meals == 0)
		the_end(ph->rules);
	while (i < ph->rules->tot)
	{
		if (ph->rules->pax[i]->dead == 1)
			the_end(ph->rules);
		i++;
		if (i == ph->rules->tot)
			i = 0;
	}
}
