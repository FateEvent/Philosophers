/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:34:06 by albaur            #+#    #+#             */
/*   Updated: 2022/07/15 16:03:25 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	get_time(t_philo *philo)
{
	long long	ms;

	gettimeofday(&philo->tv, NULL);
	ms = philo->tv.tv_sec * (uint64_t)1000 + (philo->tv.tv_usec / 1000);
	return ((ms - philo->data->runtime));
}

long long	get_time_meal(t_philo *philo, int id)
{
	if (get_time(philo) - philo->data->meal[id - 1] > philo->data->t_die)
		return (1);
	else
		return (0);
}

void	philosopher_free(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philo->data->check);
	pthread_mutex_destroy(&philo->data->dead);
	while (i < philo->data->nb)
	{
		pthread_mutex_destroy(&philo->data->forks[i]);
		++i;
	}
	free(philo->data->threads);
	free(philo->data->forks);
	free(philo->data->sophiste);
	free(philo->data->meal);
	free(philo->data);
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	size_t	i;

	if (argc < 5 || argc > 6)
		return (ft_puterror("Error: The number of arguments is incorrect."));
	if (!(sanity_check(argv)))
		return (1);
	if (!(philosopher_init(argc, argv, &philo)))
		return (ft_puterror("Error: Malloc failed to create."));
	i = 1;
	while (argv[i])
	{
		if (!ft_strtolol(argv[i]) || !ft_isnumber(argv[i]))
			return (ft_puterror("Error: Invalid arguments."));
		i++;
	}
	pthread_mutex_lock(&philo.data->dead);
	pthread_mutex_unlock(&philo.data->dead);
	philosopher_free(&philo);
	return (0);
}
