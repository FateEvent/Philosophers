/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:47:54 by faventur          #+#    #+#             */
/*   Updated: 2022/06/06 12:10:26 by faventur         ###   ########.fr       */
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
	sem_wait(rules->check);
	if (rules->pax->dead > 0)
	{
		sem_post(rules->check);
		kill(rules->pid, SIGINT);
		return (1);
	}
	sem_post(rules->check);
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
	kill(rules->pid, SIGINT);
	return (1);
}

int	check_program_end(t_sophist	*ph)
{
	sem_wait(ph->rules->check);
	if (ph->dead > 0 || check_meals(ph->rules))
	{
		sem_post(ph->rules->check);
		kill(ph->rules->pid, SIGINT);
		return (1);
	}
	sem_post(ph->rules->check);
	return (0);
}
