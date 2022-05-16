/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:57:44 by faventur          #+#    #+#             */
/*   Updated: 2022/05/16 14:41:24 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\r' || c == '\v' || c == '\f')
		return (8);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int		counter;
	int		res;
	char	*charptr;

	counter = 0;
	res = 0;
	while (*nptr && ft_isspace(*nptr))
		nptr++;
	if ((*nptr && *nptr == '-' && counter++ == 0) || (*nptr && *nptr == '+'))
		nptr++;
	charptr = (char *)nptr;
	while ((*charptr >= '0' && *charptr <= '9'))
		charptr++;
	if (counter == 0 && (charptr - nptr) > 10)
		return (-1);
	else if (counter == 1 && (charptr - nptr) > 11)
		return (0);
	while ((*nptr >= '0' && *nptr <= '9') && *nptr)
		res = res * 10 + (*nptr++ - '0');
	if (counter == 1)
		res *= -1;
	return (res);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
		*str++ = (unsigned char)c;
	return (s);
}
