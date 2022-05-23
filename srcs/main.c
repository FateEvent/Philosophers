/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/05/23 16:20:49 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	the_end(t_man ph)
{
	int	i;

	i = 0;
	while (i < ph.tot)
	{
		if (pthread_join(ph.eat, (void *)&ph.pax[i]) != 0)
		{
			perror("The thread got lost");
			return ;
		}
		if (pthread_detach(ph.eat) != 0)
		{
			perror("Boh\n");
			return ;
		}
		pthread_mutex_destroy(&ph.forks[i]);
		printf("The thread finished its execution\n");
		i++;
	}
	pthread_mutex_destroy(&ph.writing);
}

void	starting_blocks(useconds_t eating_time)
{
	while (eating_time > 0)
	{
		usleep(50 * 1000);
		eating_time -= 50;
	}
}

void	think(t_sophist philo, useconds_t reflection_time)
{
	t_man	rules;

	gettimeofday(&rules.start, NULL);
	printf("le philosophe %d etudie la religion\n", philo.id);
	printf("le philosophe %d se sent anarchiste\n", philo.id);
	printf("le philosophe %d prepare un coup d'etat\n", philo.id);
	usleep(reflection_time * 1000);
	gettimeofday(&rules.end, NULL);
	printf("time spent: %d\n", time_diff(&rules.start, &rules.end));
}

void	eat(t_sophist philo, useconds_t eating_time)
{
	t_man	rules;

	pthread_mutex_lock(&rules.writing);
	pthread_mutex_lock(&rules.forks[philo.left_fork]);
	pthread_mutex_lock(&rules.forks[philo.right_fork]);
	gettimeofday(&rules.start, NULL);
	printf("le philosophe %d prend la fourchette %d\n", philo.id, philo.left_fork);
	printf("le philosophe %d prend la fourchette %d\n", philo.id, philo.right_fork);
	usleep(eating_time * 1000);
	printf("le philosophe %d laisse tomber la fourchette %d\n", philo.id, philo.left_fork);
	printf("le philosophe %d laisse tomber la fourchette %d\n", philo.id, philo.right_fork);
	gettimeofday(&rules.end, NULL);
	printf("time spent: %d\n", time_diff(&rules.start, &rules.end));
	pthread_mutex_unlock(&rules.forks[philo.left_fork]);
	pthread_mutex_unlock(&rules.forks[philo.right_fork]);
	pthread_mutex_unlock(&rules.writing);
}

void	*routine(void *philosophical_void)
{
	t_sophist	*philo;

	philo = (t_sophist *)philosophical_void;
	while (42)
	{
		if (philo->id % 2 == 0)
		{
			starting_blocks(1500);
		}
		eat(*philo, 1500);
		think(*philo, 1500);
	}
	return (NULL);

}

void	launch(t_man ph)
{
	int	i;

	i = 0;
	while (i < ph.tot)
	{
		if (pthread_create(&ph.eat, NULL, &routine, ph.pax[i]) != 0)
			perror("Failed to create the thread");
		printf("Thread %d started\n", i);
		i++;
	}
	i = 0;
}
/*
void	init_guys(t_man ph)
{
	int	i;

	i = 0;
	while (i < ph.tot)
	{
		ph.pax[i] = (t_sophist *)malloc((sizeof(*ph.pax[i])));
		ph.pax[i]->id = i;
		ph.pax[i]->left_fork = i;
		ph.pax[i]->right_fork = (i + 1) % ph.tot;
		ph.pax[i]->dead = 0;
		pthread_mutex_init(&ph.forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&ph.writing, NULL);
}

void	init_all(t_man ph, char *argv[])
{
	ph.tot = ft_atoi(argv[1]);
	printf("%d\n",ph.tot);
	init_guys(ph);
}
*/
int	main(int argc, char *argv[])
{
	t_man		ph;
	int			i;
	int			end;
	int			death;

	(void)argc;
	death = 0;
	end = 0;
	ph.tot = ft_atoi(argv[1]);
	i = 0;

	while (i < ph.tot)
	{
		ph.pax[i] = (t_sophist *)malloc((sizeof(*ph.pax[i])));
		ph.pax[i]->id = i;
		ph.pax[i]->left_fork = i;
		ph.pax[i]->right_fork = (i + 1) % ph.tot;
		ph.pax[i]->dead = 0;
		pthread_mutex_init(&ph.forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&ph.writing, NULL);
//	init_all(ph, argv);
	launch(ph);
	while (end <= ph.tot)
	{
		if (ph.pax[end]->dead == 1)
			the_end(ph);
		end++;
		if (end == ph.tot)
			end = 0;
	}
	return (0);
}
