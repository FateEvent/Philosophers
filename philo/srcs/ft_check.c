/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:19:05 by faventur          #+#    #+#             */
/*   Updated: 2022/07/07 18:25:17 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

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

static int	ft_strtolol(const char *str)
{
	size_t		i;
	long long	rt;
	int			pm;

	if (!str)
		return (0);
	rt = 0;
	i = 0;
	pm = 1;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			pm *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		rt = rt * 10 + (str[i] - 48);
		if (rt * pm > 2147483647)
			return (0);
		else if (rt * pm < -2147483648)
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
	while (argv[i])
	{
		if (!ft_strtolol(argv[i]) || !ft_isnumber(argv[i]))
			return (ft_puterror("Error: Invalid arguments."));
		i++;
	}
	return (0);
}
