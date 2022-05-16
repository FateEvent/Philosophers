/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/05/16 15:25:59 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_sophist philo)
{
	t_man	rules;

	pthread_mutex_lock(&rules.forks[philo.left_fork]);
//	pthread_mutex_lock(&rules.forks[philo.right_fork]);
	printf("le philosophe %d prend la fourchette %d\n", philo.id, philo.left_fork);
	printf("le philosophe %d prend la fourchette %d\n", philo.id, philo.right_fork);
//	sleep(1);
	printf("le philosophe %d laisse tomber la fourchette %d\n", philo.id, philo.left_fork);
	printf("le philosophe %d laisse tomber la fourchette %d\n", philo.id, philo.right_fork);
	pthread_mutex_unlock(&rules.forks[philo.left_fork]);
//	pthread_mutex_unlock(&rules.forks[philo.right_fork]);
}

void	*routine(void *philosophical_void)
{
	t_sophist	*philo;

	philo = (t_sophist *)philosophical_void;
	eat(*philo);
	return (NULL);

}

void	launch(t_man ph)
{
	int	i;

	i = 0;
	while (i < ph.tot)
	{
		if (ph.pax[i]->id % 2 == 1)
			if (pthread_create(&ph.eat, NULL, &routine, ph.pax[i]) != 0)
				perror("Failed to create the thread");
			printf("Thread %d started\n", i);
		if (ph.pax[i]->id % 2 == 0)
		{
			if (pthread_create(&ph.eat, NULL, &routine, ph.pax[i]) != 0)
				perror("Failed to create the thread");
			printf("Thread %d started\n", i);
		}
		i++;
	}
}
/*
void	init_guys(t_man ph)
{
	int	i;

	i = 0;
	while (i < ph.tot)
	{
		ph.pax[i].id = i;
		ph.pax[i].left_fork = i;
		ph.pax[i].right_fork = (i + 1) % ph.tot;
		ph.pax[i].dead = 0;
		pthread_mutex_init(&ph.forks[i], NULL);
	}
}

void	init_all(t_man ph, char *argv[])
{
	ph.tot = ft_atoi(argv[1]);
	printf("%d\n",ph.tot);
}
*/
int	main(int argc, char *argv[])
{
	t_man		ph;
	int			i;

	(void)argc;

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


//	init_all(ph, argv);
//	init_guys(ph);
	launch(ph);
	i = 0;
	while (i < ph.tot)
	{
		if (pthread_join(ph.eat, (void *)&ph.pax[i]) != 0)
		{
			perror("The thread got lost");
			return (1);
		}
		pthread_mutex_destroy(&ph.forks[i]);
		printf("The thread finished its execution\n");
		i++;
	}
	return (0);
}
