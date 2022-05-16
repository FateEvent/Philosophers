/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:06:01 by faventur          #+#    #+#             */
/*   Updated: 2022/05/16 17:05:35 by faventur         ###   ########.fr       */
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
	int				id;
	int				right_fork;
	int				left_fork;
	int				dead;
}				t_sophist;

typedef struct s_man
{
	int					tot;
	struct s_sophist	*pax[250];
	pthread_t			eat;
	pthread_mutex_t		forks[250];
	struct timeval		start;
	struct timeval		end;
}				t_man;

void	*ft_memset(void *s, int c, size_t n);
int		ft_atoi(const char *nptr);

int		time_diff(struct timeval *start, struct timeval *end);

#endif