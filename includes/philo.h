/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:06:01 by faventur          #+#    #+#             */
/*   Updated: 2022/05/23 18:53:50 by faventur         ###   ########.fr       */
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
	pthread_t		pt;
}				t_sophist;

typedef struct s_man
{
	int					tot;
	struct s_sophist	*pax[250];
	pthread_mutex_t		forks[250];
	pthread_mutex_t		meal;
	pthread_mutex_t		writing;
	struct timeval		start;
	struct timeval		end;
	suseconds_t			eating_time;
	suseconds_t			time_to_sleep;
}				t_man;

void	*ft_memset(void *s, int c, size_t n);
int		ft_atoi(const char *nptr);

void	*routine(void *philosophical_void);
void	eat(t_sophist philo, t_man rules, useconds_t eating_time);
void	think(t_sophist philo, t_man rules, useconds_t reflection_time);
void	take_notes(t_sophist philo, t_man rules, char *msg);
void	the_end(t_man ph);

t_man	init_all(char *argv[]);
void	launch(t_man ph);

void	starting_blocks(useconds_t eating_time);
int		time_diff(struct timeval *start, struct timeval *end);

#endif