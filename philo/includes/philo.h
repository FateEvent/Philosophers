/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:06:01 by faventur          #+#    #+#             */
/*   Updated: 2022/07/13 16:32:14 by faventur         ###   ########.fr       */
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
	long			meals_num;
	struct timeval	acting;
	struct timeval	last_meal;
	pthread_t		pt;
	struct s_man	*rules;
}				t_sophist;

typedef struct s_man
{
	int					tot;
	int					deaths;
	struct s_sophist	*pax[200];
	pthread_mutex_t		*forks;
	pthread_mutex_t		meal;
	pthread_mutex_t		writing;
	pthread_mutex_t		check;
	struct timeval		start;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	long				num_of_meals;
}				t_man;

int		ft_atoi(const char *nptr);
int		ft_puterror(const char *str);

void	*routine(void *philosophical_void);
void	happy_hour(t_sophist *philo, t_man *rules);
void	eat(t_sophist philo);
void	think(t_sophist philo);
void	ft_sleep(t_sophist philo);
void	take_notes(t_sophist philo, char *msg);
void	solitude(t_sophist *philo);
void	the_end(t_man *rules);

t_man	*init_all(char *argv[]);
void	launch(t_man *ph);

void	timecount(t_sophist philo, long duration);
void	countdown(t_sophist philo, long duration);
long	time_diff(struct timeval *start, struct timeval *end);
long	length_diff(long present, long past);
long	get_the_time(void);
int		time_goes_by(struct timeval *time, long standard);

int		check_program_end(t_sophist	*ph);
int		check_meals(t_man *rules);
int		check_deaths(t_man *rules);
int		death_note(t_sophist *philo);
int		check_args(int argc, char *argv[]);

#endif