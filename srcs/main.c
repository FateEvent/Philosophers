/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/05/26 22:39:37 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philosophical_void)
{
	t_sophist	*philo;
	t_man		*rules;

	philo = (t_sophist *)philosophical_void;
	rules = philo->rules;
	if (rules->tot == 1)
		ft_sleep(*philo);
	if ((rules->tot % 2 == 1 && philo->id == philo->rules->tot - 1)
		|| philo->id % 2 == 0)
	{
		gettimeofday(&philo->acting, NULL);
		timecount(*philo, rules->time_to_eat);
	}
	while (!check_program_end(philo))
	{
		eat(*philo);
		gettimeofday(&philo->last_meal, NULL);
		philo->meals_num++;
		think(*philo);
		ft_sleep(*philo);
	}
	return (NULL);
}

void	launch(t_man *ph)
{
	int	i;

	i = 0;
	gettimeofday(&ph->start, NULL);
	while (i < ph->tot)
	{
		if (pthread_create(&ph->pax[i]->pt, NULL, &routine, ph->pax[i]) != 0)
			perror("Failed to create the thread");
		printf("Thread %d started\n", i);
		i++;
	}
	i = 0;
}

static void	ft_update_struct(t_man *ph, char *argv[])
{
	ph->tot = ft_atoi(argv[1]);
	ph->deaths = 0;
	ph->happy_meals = 0;
	ph->time_to_die = ft_atoi(argv[2]);
	ph->time_to_eat = ft_atoi(argv[3]);
	ph->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		ph->num_of_meals = ft_atoi(argv[5]);
		printf("%ld\n", ph->num_of_meals);
	}
	else
		ph->num_of_meals = -1;
}

t_man	*init_all(char *argv[])
{
	t_man	*ph;
	int		i;

	ph = (t_man *)malloc(sizeof(*ph) * ft_atoi(argv[1]));
	if (!ph)
		return (NULL);	//error marking
	ft_update_struct(ph, argv);
	i = 0;
	while (i < ph->tot)
	{
		ph->pax[i] = (t_sophist *)malloc((sizeof(*ph->pax[i])));
		if (!ph->pax[i])
			return (NULL);	//error marking
		ph->pax[i]->id = i;
		ph->pax[i]->left_fork = i;
		ph->pax[i]->right_fork = (i + 1) % ph->tot;
		ph->pax[i]->meals_num = 0;
		ph->pax[i]->dead = 0;
		ph->pax[i]->rules = ph;
		pthread_mutex_init(&ph->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&ph->writing, NULL);
	return (ph);
}

int	main(int argc, char *argv[])
{
	t_man	*ph;

	if (check_args(argc))
	{
		ph = init_all(argv);
		launch(ph);
		while (!ph->deaths || !ph->num_of_meals)
			if (check_meals(ph))
				break ;
		the_end(ph);
		return (0);
	}
}
