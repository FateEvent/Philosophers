/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:47:54 by faventur          #+#    #+#             */
/*   Updated: 2022/05/24 18:05:05 by faventur         ###   ########.fr       */
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

void	check_death(t_sophist *philo)
{
	if (philo->many_meals > 0)
	{
		if (time_goes_by(&philo->last_meal, philo->rules->time_to_eat))
			philo->dead = 1;
	}
	else
	{
		if (time_goes_by(&philo->rules->start, philo->rules->time_to_eat))
			philo->dead = 1;
	}
}

void	check_program_end(t_sophist	*ph)
{
	int		i;

	i = 0;
	while (i <= ph->rules->tot)
	{
		if (ph->rules->pax[i]->dead == 1)
			the_end(ph->rules);
		i++;
		if (i == ph->rules->tot)
			i = 0;
	}
}
