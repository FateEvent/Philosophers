/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/06/06 15:22:44 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	launch(t_man *rules)
{
	int	i;

	i = 0;
	rules->forks = sem_open("fourchette", O_CREAT | O_EXCL, 0644, rules->tot / 2);
	rules->check = sem_open("sem_check", O_CREAT | O_EXCL, 0644, 1);
	rules->writing = sem_open("writing", O_CREAT | O_EXCL, 0644, 1);
//	gettimeofday(&rules->start, NULL);
	while (i < rules->tot)
	{
		rules->pid = fork();
		if (rules->pid < 0)
		{
			ft_puterror("Error: Failed to create the fork.");
			sem_unlink("fourchette");
			sem_unlink("sem_check");
			sem_unlink("writing");
			sem_close(rules->forks);
			sem_close(rules->check);
			sem_close(rules->writing);
		}
		else if (rules->pid == 0)
		{
			gettimeofday(&rules->start, NULL);
			rules->pax = (t_sophist *)malloc(sizeof(*rules->pax));
			if (!rules->pax)
				return ;
			rules->pax->id = i;
			rules->pax->meals_num = 0;
			rules->pax->dead = 0;
			rules->pax->rules = rules;
			break ;
		}
		i++;
	}
	if (rules->pid == 0)
		happy_hour(rules->pax);
	else
	{
		printf("je suis moi!");
		while (waitpid(-1, NULL, 0))
		{
			if (errno == ECHILD)
				break ;
		}
		sem_unlink("fourchette");
		sem_unlink("sem_check");
		sem_unlink("writing");
		sem_close(rules->forks);
		sem_close(rules->check);
		sem_close(rules->writing);
	}
}

t_man	*init_all(char *argv[])
{
	t_man	*rules;

	rules = (t_man *)malloc(sizeof(*rules) * ft_atoi(argv[1]));
	if (!rules)
		return (NULL);
	rules->tot = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		rules->num_of_meals = ft_atoi(argv[5]);
	else
		rules->num_of_meals = -1;
	return (rules);
}

int	main(int argc, char *argv[])
{
	t_man	*rules;

	if (check_args(argc, argv))
	{
		rules = init_all(argv);
		if (!rules)
			return (1);
		launch(rules);
		/*
		while (!rules->pax->dead)
			;
		the_end(rules);
		*/
		return (0);
	}
}
