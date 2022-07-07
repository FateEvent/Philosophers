/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:47:54 by faventur          #+#    #+#             */
/*   Updated: 2022/07/07 18:13:56 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isnumber(char *nptr)
{
	int	i;

	i = 0;
	if (nptr[i] == '-')
		i++;
	if (nptr[i] == ' ' || nptr[i] == '\0')
		return (0);
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char *argv[])
{
	size_t	i;

	if (argc < 5 || argc > 6)
		return (ft_puterror("Error: The number of arguments is incorrect."));
	if (ft_atoi(argv[1]) <= 0)
		return (ft_puterror("Error: There are no philosophers."));
	if (ft_atoi(argv[1]) > 200)
		return (ft_puterror("Error: Program softcapped at 200 philosophers."));
	i = 1;
	while (argv[i++])
	{
		if (!ft_strtolol(argv[i]) || !ft_isnumber(argv[i]))
			return (ft_puterror("Error: At least one of the argument \
				is not a valid number."));
		i++;
	}
	return (0);
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
