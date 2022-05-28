/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:47:54 by faventur          #+#    #+#             */
/*   Updated: 2022/05/28 10:42:36 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		ft_puterror("Error: The number of arguments is incorrect.");
		return (0);
	}
	if (ft_atoi(argv[1]) > 200)
	{
		ft_puterror("Error: Program softcapped at 200 philosophers.");
		return (0);
	}
	return (1);
}

int	check_deaths(t_man *rules)
{
	int	i;

	i = 0;
	while (i < rules->tot)
	{
		if (rules->pax[i]->dead > 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_meals(t_man *rules)
{
	int	i;
	int	cmp;

	i = 0;
	if (rules->num_of_meals < 0)
		return (0);
	cmp = rules->num_of_meals;
	while (i < rules->tot)
	{
		if (rules->pax[i]->meals_num < cmp)
			return (0);
		i++;
	}
	rules->deaths = 1;
	return (1);
}

int	check_program_end(t_sophist	*ph)
{
	pthread_mutex_lock(&ph->rules->check);
	if (ph->rules->deaths > 0)
	{
		pthread_mutex_unlock(&ph->rules->check);
		return (1);
	}
	pthread_mutex_unlock(&ph->rules->check);
	return (0);
}
