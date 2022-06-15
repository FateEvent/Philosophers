/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:47:54 by faventur          #+#    #+#             */
/*   Updated: 2022/06/15 11:35:58 by faventur         ###   ########.fr       */
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
	if (rules->data->dead > 0)
	{
		sem_post(rules->check);
		the_game_ends(rules);
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
	if (rules->data->meals_num <= cmp)
		return (0);
	the_game_ends(rules);
	return (1);
}

int	check_program_end(t_data *ph)
{
	printf("qui!\n");
	sem_wait(ph->rules->check);
	if (check_deaths(ph->rules) || check_meals(ph->rules))
	{
		printf("bambambam\n");
		sem_post(ph->rules->check);
		the_game_ends(ph->rules);
		return (1);
	}
	sem_post(ph->rules->check);
	return (0);
}
