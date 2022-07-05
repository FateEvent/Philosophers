/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/07/05 17:45:47 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	launch(t_man *rules)
{
	pthread_t	pt;
	int			i;

	i = 0;
	rules->forks = sem_open("fourchette", O_CREAT | O_EXCL, 0644, rules->tot / 2);
	rules->check = sem_open("sem_check", O_CREAT | O_EXCL, 0644, 1);
	rules->writing = sem_open("writing", O_CREAT | O_EXCL, 0644, 1);
	gettimeofday(&rules->start, NULL);
	while (i < rules->tot)
	{
		rules->pid[i] = fork();
		if (rules->pid[i] < 0)
		{
			ft_puterror("Error: Failed to create the fork.");
			sem_unlink("fourchette");
			sem_unlink("sem_check");
			sem_unlink("writing");
			sem_close(rules->forks);
			sem_close(rules->check);
			sem_close(rules->writing);
		}
		if (rules->pid[i] == 0)
		{
			rules->pax->id = i;
			happy_hour(rules->pax);
			exit(0);
		}
		if (i % 2 == 0)
			usleep(rules->time_to_eat);
		i++;
	}
	pthread_create(&pt, NULL, wait_pid_end, rules);
	pthread_detach(pt);
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
	rules->pax = (t_sophist *)malloc(sizeof(*rules->pax));
	if (!rules->pax)
		return (NULL);
	rules->pax->meals_num = 0;
	rules->pax->dead = 0;
	rules->pax->rules = rules;
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
		the_end(rules);
		return (0);
	}
}
