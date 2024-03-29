/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:06:01 by faventur          #+#    #+#             */
/*   Updated: 2022/07/27 13:50:37 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>
# include <errno.h>

typedef struct s_sophist
{
	int				id;
	int				dead;
	long			meals_num;
	long long		runtime;
	long long		last_meal;
	struct timeval	tva;
	struct timeval	acting;
	struct s_man	*rules;
}				t_sophist;

typedef struct s_man
{
	int					tot;
	struct s_sophist	*pax;
	sem_t				*forks;
	sem_t				*check;
	sem_t				*writing;
	pid_t				pid[200];
	pthread_t			pt;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	long				num_of_meals;
}				t_man;

void		*ft_memset(void *s, int c, size_t n);
int			ft_atoi(const char *nptr);
int			ft_puterror(const char *str);

void		philosopher_manage(t_sophist *philo);
void		*happy_hour(t_sophist *philo);
void		eat(t_sophist *philo);
void		think(t_sophist *philo);
void		ft_sleep(t_sophist *philo);
void		take_notes(t_sophist *philo, char *msg);
void		solitude(t_sophist *philo);
void		the_end(t_man *rules);

void		*wait_pid_end(void *rules);
void		*the_policeman(void *rules);

t_man		*init_all(char *argv[]);
void		launch(t_man *ph);

void		countdown(t_sophist *philo, long duration);
long		time_diff(struct timeval *start, struct timeval *end);
long		length_diff(long present, long past);
long		get_the_time(void);
long long	ft_get_time(t_sophist *philo);

int			death_note(t_sophist *philo);
int			check_args(int argc, char *argv[]);

#endif