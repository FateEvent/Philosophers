/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanity_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:42:44 by albaur            #+#    #+#             */
/*   Updated: 2022/07/15 16:13:15 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	num_check(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			++j;
		}
		j = 0;
		++i;
	}
	return (1);
}

static int	min_check(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 1)
			return (0);
		++i;
	}
	return (1);
}

int	sanity_check(char **argv)
{
	if (!(num_check(argv)))
		return (ft_puterror("Error: Only numbers are accepted."));
	if (!(min_check(argv)))
		return (ft_puterror("Error: Numbers must be greater than 0."));
	if (ft_atoi(argv[1]) > 200)
		return (ft_puterror("Error: Program softcapped at 200 philosophers."));
	return (0);
}
