/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/05/23 18:38:32 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch(t_man ph)
{
	int	i;

	i = 0;
	while (i < ph.tot)
	{
		if (pthread_create(&ph.pax[i]->pt, NULL, &routine, ph.pax[i]) != 0)
			perror("Failed to create the thread");
		printf("Thread %d started\n", i);
		i++;
	}
	i = 0;
}

t_man	init_all(char *argv[])
{
	t_man	ph;
	int		i;

	ph.tot = ft_atoi(argv[1]);
//	ph.eating_time = ft_atoi(argv[3]);
	ph.eating_time = 1500;
//	ph.time_to_sleep = ft_atoi(argv[4]);
	ph.time_to_sleep = 2000;
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
	return (ph);
}

int	main(int argc, char *argv[])
{
	t_man	ph;
	int		end;
	int		death;

	(void)argc;
	death = 0;
	end = 0;
	ph = init_all(argv);
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