/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/06/06 12:13:10 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	launch(t_man *ph)
{
	int	i;

	i = 0;
	ph->forks = sem_open("fourchette", O_CREAT | O_EXCL, 0644, ph->tot / 2);
	ph->check = sem_open("sem_check", O_CREAT | O_EXCL, 0644, 1);
	ph->writing = sem_open("writing", O_CREAT | O_EXCL, 0644, 1);
	gettimeofday(&ph->start, NULL);
	while (i < ph->tot)
	{
		ph->pid = fork();
		if (ph->pid < 0)
		{
			ft_puterror("Error: Failed to create the fork.");
			sem_unlink("fourchette");
			sem_unlink("sem_check");
			sem_unlink("writing");
			sem_close(ph->forks);
			sem_close(ph->check);
			sem_close(ph->writing);
		}
		else if (ph->pid == 0)
			break ;
		ph->pax = (t_sophist *)malloc(sizeof(*ph->pax));
		if (!ph->pax)
			return ;
		ph->pax->id = i;
		ph->pax->meals_num = 0;
		ph->pax->dead = 0;
		ph->pax->rules = ph;
		i++;
	}
	if (ph->pid == 0)
		happy_hour(ph->pax);
	else
	{
		while (waitpid(-1, NULL, 0))
		{
			if (errno == ECHILD)
				break ;
		}
		sem_unlink("fourchette");
		sem_unlink("sem_check");
		sem_unlink("writing");
		sem_close(ph->forks);
		sem_close(ph->check);
		sem_close(ph->writing);
	}
}

static void	ft_update_struct(t_man *ph, char *argv[])
{
	ph->tot = ft_atoi(argv[1]);
	ph->time_to_die = ft_atoi(argv[2]);
	ph->time_to_eat = ft_atoi(argv[3]);
	ph->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		ph->num_of_meals = ft_atoi(argv[5]);
	else
		ph->num_of_meals = -1;
}

t_man	*init_all(char *argv[])
{
	t_man	*ph;
	int		i;

	ph = (t_man *)malloc(sizeof(*ph) * ft_atoi(argv[1]));
	if (!ph)
		return (NULL);
	ft_update_struct(ph, argv);
	i = 0;
	return (ph);
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
		while (!rules->pax->dead)
			if (check_deaths(rules) || check_meals(rules))
				break ;
		the_end(rules);
		return (0);
	}
}
