/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/05/14 19:23:27 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <time.h>

int	x = 0;
pthread_mutex_t	mutex;

void	*roll_dice(void *s)
{
	int	value;
	int	*result;

	value = (rand() % 6) + 1;
	result = (int *)malloc(sizeof(int));
	*result = value;
	s = result;
	return (s);
}

/*
void	*eat(void *s)
{
	printf("le philosophe mange et compte: %d\n", x);
	sleep(1);
	printf("ending thread\n");
	s = NULL;
	return (s);
}
*/
void	*count(void *s)
{
	long int	i = 0;

	while (i++ < 5)
	{
		pthread_mutex_lock(&mutex);
		x++;
//		printf("le philosophe compte, %d\n", x);
		pthread_mutex_unlock(&mutex);
	}
	s = NULL;
	return (s);
}

int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*routine(void *arg)
{
	int	index = *(int *)arg;
	printf("%d\n", primes[index]);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t	pt[10];
	int			i;

	(void)argc;
	(void)argv;
	i = 0;
	while (i < 10)
	{
		if (pthread_create(&pt[i], NULL, &routine, &i) != 0)
		{
			perror("Failed to create a thread");
			return (1);
		}
		sleep(1);
		printf("Thread %d started\n", i);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (pthread_join(pt[i], NULL) != 0)
		{
			perror("A thread got lost");
			return (1);
		}
		printf("Thread %d finished its execution\n", i);
		i++;
	}
	return (0);
}

/*
int	main(int argc, char *argv[])
{
	pthread_t	*pt;
	srand(time(NULL));
	int			i, j;
	int			*res;

	if (argc == 2)
	{
		pt = (pthread_t *)malloc(sizeof(*pt) * (atoi(argv[1])));
		i = 0;
		pthread_mutex_init(&mutex, NULL);
		while (i < atoi(argv[1]))
		{
			if (pthread_create(&pt[i], NULL, &count, NULL) != 0)
			{
				perror("Failed to create a thread");
				return (1);
			}
			printf("Thread %d started\n", i);
			i++;
		}
		j = 0;
		while (j < atoi(argv[1]))
		{
			if (pthread_join(pt[j], NULL) != 0)
			{
				perror("A thread got lost");
				return (1);
			}
			printf("Thread %d finished its execution\n", j);
			j++;
		}
		pthread_mutex_destroy(&mutex);
		printf("x %d\n", x);
		free(pt);
		return (0);
	}
	else
	{
		pt = (pthread_t *)malloc(sizeof(*pt) * 8);
		i = 0;
//		pthread_mutex_init(&mutex, NULL);
		while (i < 8)
		{
			if (pthread_create(&pt[i], NULL, &roll_dice, NULL) != 0)
			{
				perror("Failed to create a thread");
				return (1);
			}
			printf("Thread %d started\n", i);
			i++;
		}
		j = 0;
		while (j < 8)
		{
			if (pthread_join(pt[j], (void **)&res) != 0)
			{
				perror("A thread got lost");
				return (1);
			}
			printf("Thread %d finished its execution\n", j);
			printf("Result: %d\n", *res);
			j++;
		}
//		pthread_mutex_destroy(&mutex);
		free(res);
		free(pt);
		return (0);
	}
}
*/