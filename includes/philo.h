/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:06:01 by faventur          #+#    #+#             */
/*   Updated: 2022/05/16 12:17:41 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_sophist
{
	int				nbr;
	int				fork_nbr;
	unsigned int	id[200];
	unsigned int	forks[200];
	int				dead;
	pthread_t		pt;
	pthread_t		eat;
	pthread_mutex_t	mutex;
}				t_sophist;

void	*ft_memset(void *s, int c, size_t n);
int		ft_atoi(const char *nptr);

#endif