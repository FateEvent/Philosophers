/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/06/05 18:38:52 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	launch(pid_t pid, t_man *ph)
{
	int	i;

	i = 0;
	ph->forks = sem_open("fourchette", O_CREAT | O_EXCL, 0644, ph->tot / 2);
	ph->check = sem_open("sem_check", O_CREAT | O_EXCL, 0644, 1);
	gettimeofday(&ph->start, NULL);
	while (i < ph->tot)
	{
		pid = fork();
		if (pid < 0)
		{
			ft_puterror("Error: Failed to create the fork.");
			sem_unlink("fourchette");
			sem_unlink("sem_check");
			sem_close(ph->forks);
			sem_close(ph->check);
		}
		else if (pid == 0)
			break ;
		i++;
	}
	if (pid == 0)
		happy_hour(ph->pax[i]);
	else if (pid > 0)
	{
		while ((pid = waitpid(-1, NULL, 0)))
		{
			if (errno == ECHILD)
				break ;
		}
		sem_unlink("fourchette");
		sem_unlink("sem_check");
		sem_close(ph->forks);
		sem_close(ph->check);
	}
}

static void	ft_update_struct(t_man *ph, char *argv[])
{
	ph->tot = ft_atoi(argv[1]);
	ph->deaths = 0;
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
	while (i < ph->tot)
	{
		ph->pax[i] = (t_sophist *)malloc((sizeof(*ph->pax[i])));
		if (!ph->pax[i])
			return (NULL);
		ph->pax[i]->id = i;
		ph->pax[i]->meals_num = 0;
		ph->pax[i]->dead = 0;
		ph->pax[i]->rules = ph;
		i++;
	}
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
		rules->pid = 0;
		launch(rules->pid, rules);
		while (!rules->deaths)
			if (check_deaths(rules) || check_meals(rules))
				break ;
		the_end(rules->pid);
		return (0);
	}
}
