/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:47:54 by faventur          #+#    #+#             */
/*   Updated: 2022/05/26 20:44:05 by faventur         ###   ########.fr       */
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
	{
		rules->num_of_meals--;
		if (rules->num_of_meals == 0)
			the_end(rules);
		printf("%ld\n", rules->num_of_meals);
	}
	return (1);
}

int	death_note(t_sophist *philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (philo->meals_num > 0)
	{
		if (time_diff(&philo->last_meal, &now) > philo->rules->time_to_die)
		{
			philo->dead = 1;
			philo->rules->deaths = 1;
			take_notes(*philo, "has died\n");
			the_end(philo->rules);
		}
	}
	else if (philo->meals_num == 0)
	{
		if (time_diff(&philo->rules->start, &now) > philo->rules->time_to_die)
		{
			philo->dead = 1;
			philo->rules->deaths = 1;
			take_notes(*philo, "has died\n");
			the_end(philo->rules);
		}
	}
	return (0);
}

void	check_program_end(t_sophist	*ph)
{
	if (ph->rules->num_of_meals == 0)
		the_end(ph->rules);
	if (ph->rules->deaths > 0)
		the_end(ph->rules);
}
