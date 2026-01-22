/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokdas <ogokdas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:29:31 by ogokdas           #+#    #+#             */
/*   Updated: 2026/01/22 17:24:14 by ogokdas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			return (-1);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		if (result > 2147483647)
			return (-1);
		i++;
	}
	if (nptr[i] != '\0')
		return (-1);
	return (result);
}

int	parse(int ac, char **av)
{
	int	i;
	int	value;

	if (ac != 5 && ac != 6)
		return (printf("Error\n"), 1);
	i = 1;
	while (i < ac)
	{
		value = ft_atoi(av[i]);
		if (value <= 0)
			return (printf("Error\n"), 1);
		i++;
	}
	return (0);
}

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ms_sleep(int time)
{
	long long	dest_time;

	dest_time = get_time() + time;
	while (get_time() < dest_time)
		usleep(100);
}

void	philo_print(t_philo *philo, int id, char *str)
{
	pthread_mutex_lock(philo->info->lock_dead);
	pthread_mutex_lock(philo->info->lock_write);
	if (philo->info->is_dead == 0)
		printf("%llu %d %s\n",
			get_time() - philo->info->start_time, id, str);
	pthread_mutex_unlock(philo->info->lock_write);
	pthread_mutex_unlock(philo->info->lock_dead);
}
