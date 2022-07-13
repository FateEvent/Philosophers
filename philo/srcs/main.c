/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/07/13 20:05:42 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch(t_man *rules)
{
	int	i;

	i = 0;
	gettimeofday(&rules->start, NULL);
	while (i < rules->tot)
	{
		if (pthread_create(&rules->pax[i]->pt, NULL,
				&routine, rules->pax[i]) != 0)
			ft_puterror("Error: Failed to create the thread.");
		i++;
	}
}

static void	ft_update_struct(t_man *rules, char *argv[])
{
	rules->tot = ft_atoi(argv[1]);
	rules->deaths = 0;
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->tot);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		rules->num_of_meals = ft_atoi(argv[5]);
	else
		rules->num_of_meals = -1;
}

t_man	*init_all(char *argv[])
{
	t_man	*rules;
	int		i;

	rules = (t_man *)malloc(sizeof(*rules) * ft_atoi(argv[1]));
	if (!rules)
		return (NULL);
	ft_update_struct(rules, argv);
	i = 0;
	while (i < rules->tot)
	{
		rules->pax[i] = (t_sophist *)malloc(sizeof(*rules->pax[i]));
		if (!rules->pax[i])
			return (NULL);
		rules->pax[i]->id = i;
		rules->pax[i]->left_fork = i;
		pthread_mutex_init(&rules->forks[i], NULL);
		rules->pax[i]->right_fork = (i + 1) % rules->tot;
		rules->pax[i]->meals_num = 0;
		rules->pax[i]->dead = 0;
		rules->pax[i]->rules = rules;
		i++;
	}
	pthread_mutex_init(&rules->writing, NULL);
	pthread_mutex_init(&rules->check, NULL);
	return (rules);
}

int	main(int argc, char *argv[])
{
	t_man	*rules;
	int		i;

	if (!check_args(argc, argv))
	{
		i = 0;
		rules = init_all(argv);
		if (!rules)
			return (1);
		launch(rules);
/*
		while (!rules->deaths && i < rules->tot)
		{
			if (check_deaths(rules->pax[i]) || check_meals(rules->pax[i]))
				break ;
			if (i == rules->tot - 1)
				i = 0;
			i++;
		}
*/
		pthread_mutex_lock(&rules->check);
		the_end(rules);
		return (0);
	}
}
