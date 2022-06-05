/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:06:01 by faventur          #+#    #+#             */
/*   Updated: 2022/06/05 18:30:10 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <errno.h>

typedef struct s_sophist
{
	int				id;
	int				dead;
	long			meals_num;
	struct timeval	acting;
	struct timeval	last_meal;
	struct s_man	*rules;
}				t_sophist;

typedef struct s_man
{
	int					tot;
	int					deaths;
	struct s_sophist	*pax[200];
	sem_t				*forks;
	sem_t				*check;
	pid_t				pid;
	struct timeval		start;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	long				num_of_meals;
}				t_man;

void	*ft_memset(void *s, int c, size_t n);
void	ft_puterror(const char *str);
int		ft_atoi(const char *nptr);

void	*happy_hour(t_sophist *philo);
void	eat(t_sophist philo);
void	think(t_sophist philo);
void	ft_sleep(t_sophist philo);
void	take_notes(t_sophist philo, char *msg);
void	solitude(t_sophist *philo);
void	the_end(pid_t pid);

t_man	*init_all(char *argv[]);
void	launch(pid_t pid, t_man *ph);

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