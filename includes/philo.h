/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:06:01 by faventur          #+#    #+#             */
/*   Updated: 2022/05/24 18:27:11 by faventur         ###   ########.fr       */
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
	long			many_meals;
	struct timeval	acting;
	struct timeval	last_meal;
	pthread_t		pt;
	struct s_man	*rules;
}				t_sophist;

typedef struct s_man
{
	int					tot;
	struct s_sophist	*pax[200];
	pthread_mutex_t		forks[200];
	pthread_mutex_t		meal;
	pthread_mutex_t		writing;
	struct timeval		start;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	long				num_of_meals;
}				t_man;

void	*ft_memset(void *s, int c, size_t n);
void	ft_puterror(const char *str);
int		ft_atoi(const char *nptr);

void	*routine(void *philosophical_void);
void	eat(t_sophist philo);
void	think(t_sophist philo);
void	take_notes(t_sophist philo, char *msg);
void	the_end(t_man *rules);

t_man	*init_all(char *argv[]);
void	launch(t_man *ph);

void	timecount(t_sophist philo, long duration);
long	time_diff(struct timeval *start, struct timeval *end);
long	length_diff(long present, long past);
long	get_the_time(void);
int		time_goes_by(struct timeval *time, long standard);

void	check_death(t_sophist *philo);
void	check_program_end(t_sophist	*ph);
int		check_args(int argc);

#endif