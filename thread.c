/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokdas <ogokdas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:02:24 by ogokdas           #+#    #+#             */
/*   Updated: 2026/01/30 16:24:10 by ogokdas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_hungry(t_info *inf, int i)
{
	long long	time;

	pthread_mutex_lock(&inf->phi[i].lock_meal);
	time = get_time() - inf->start_time;
	if (time - inf->phi[i].last_meal_time > inf->die_time)
	{
		pthread_mutex_lock(inf->lock_dead);
		inf->is_dead = 1;
		pthread_mutex_lock(inf->lock_write);
		printf("%lld %d died\n", time, inf->phi[i].id);
		pthread_mutex_unlock(inf->lock_write);
		pthread_mutex_unlock(inf->lock_dead);
		pthread_mutex_unlock(&inf->phi[i].lock_meal);
		return (1);
	}
	pthread_mutex_unlock(&inf->phi[i].lock_meal);
	return (0);
}

void	*is_dead(void *av)
{
	t_info	*inf;
	int		i;

	inf = (t_info *)av;
	while (1)
	{
		i = 0;
		while (i < inf->number_philos)
		{
			pthread_mutex_lock(inf->lock_dead);
			if (inf->is_dead != 0)
			{
				pthread_mutex_unlock(inf->lock_dead);
				return (NULL);
			}
			pthread_mutex_unlock(inf->lock_dead);
			if (is_hungry(inf, i))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	must_eat_checking(t_info *inf, int count)
{
	if (count == inf->number_philos)
	{
		pthread_mutex_lock(inf->lock_dead);
		inf->is_dead = 2;
		pthread_mutex_unlock(inf->lock_dead);
		return (1);
	}
	return (0);
}

int	count_full_philos(t_info *inf)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < inf->number_philos)
	{
		pthread_mutex_lock(&inf->phi[i].lock_meal);
		if (inf->phi[i].eat_count >= inf->must_eat)
			count++;
		pthread_mutex_unlock(&inf->phi[i].lock_meal);
		i++;
	}
	return (count);
}

void	*must_eat(void *av)
{
	t_info	*inf;

	inf = (t_info *)av;
	if (inf->must_eat == -1)
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(inf->lock_dead);
		if (inf->is_dead)
		{
			pthread_mutex_unlock(inf->lock_dead);
			return (NULL);
		}
		pthread_mutex_unlock(inf->lock_dead);
		if (must_eat_checking(inf, count_full_philos(inf)))
			return (NULL);
	}
	return (NULL);
}
