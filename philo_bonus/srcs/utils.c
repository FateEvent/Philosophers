/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:47:54 by faventur          #+#    #+#             */
/*   Updated: 2022/07/07 16:55:28 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_args(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		ft_puterror("Error: The number of arguments is incorrect.");
		return (0);
	}
	if (ft_atoi(argv[1]) <= 0)
	{
		ft_puterror("Error: There are no philosophers.");
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
	if (rules->pax->dead > 0)
	{
		return (1);
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
	if (rules->pax->meals_num <= cmp)
		return (0);
	sem_post(rules->check);
	return (1);
}
