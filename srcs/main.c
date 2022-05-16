/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/05/16 12:19:40 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eat(void *param)
{
	t_sophist	*ph;

	ph = (t_sophist *)param;
	while (ph->fork_nbr)
	{
		pthread_mutex_lock(&ph->mutex);
		printf("le philosophe numero %d mange\n", ph->*(ptr));
		sleep(1);
		printf("ending thread\n");
		pthread_mutex_unlock(&ph->mutex);
	}
	return (NULL);
}

void	launch(t_sophist *ph)
{
	int	i;
	int	*ptr;

	i = 0;
	while (i < ph->nbr)
	{
		ph->id[i] = i;
		if (ph->id[i] % 2 == 1 && ph->id[i] != ph->nbr - 1)
			if (pthread_create(&ph->eat, NULL, &eat, (void *)ph) != 0)
				perror("Failed to create the thread");
		if (ph->id[i] % 2 == 0 && ph->id[i] != ph->nbr - 1)
		{
			sleep(0.1);
			if (pthread_create(&ph->eat, NULL, &eat, &ph) != 0)
				perror("Failed to create the thread");
		}
		i++;
	}
}

void	init(t_sophist *ph, char *argv[])
{
	ph->nbr = ft_atoi(argv[1]);
	ph->fork_nbr = ft_atoi(argv[1]);
	ph->dead = 0;
	pthread_mutex_init(&ph->mutex, NULL);
}

int	main(int argc, char *argv[])
{
	t_sophist	*ph;
	int			i;

	init(ph, argv);
	launch(ph);
	i = 0;
	(void)argc;
	printf("Thread %d started\n", i);
	while (i < ph->nbr)
	{
		if (pthread_join(ph->pt, NULL) != 0)
		{
			perror("The thread got lost");
			return (1);
		}
		printf("The thread finished its execution\n");
		i++;
	}
	pthread_mutex_destroy(&ph->mutex);
	return (0);
}
