/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokdas <ogokdas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:52:34 by ogokdas           #+#    #+#             */
/*   Updated: 2026/01/22 19:50:02 by ogokdas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_hungry(t_info *inf, int i)
{
	long long	time;

	pthread_mutex_lock(&inf->filo[i].lock_meal);
	time = get_time() - inf->start_time;
	if (time - inf->filo[i].last_meal_time > inf->die_time)
	{
		pthread_mutex_lock(inf->lock_dead);
		inf->is_dead = 1;
		pthread_mutex_lock(inf->lock_write);
		printf("%llu %d died\n", time, inf->filo[i].id);
		pthread_mutex_unlock(inf->lock_write);
		pthread_mutex_unlock(inf->lock_dead);
		pthread_mutex_unlock(&inf->filo[i].lock_meal);
		return (1);
	}
	pthread_mutex_unlock(&inf->filo[i].lock_meal);
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
			if (inf->is_dead != 0)
				return (NULL);
			if (is_hungry(inf, i))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
int must_eat_checking(t_info *inf, int count)
{

	if (count == inf->number_philos)
	{

		pthread_mutex_lock(inf->lock_dead);
		inf->is_dead = 2;
		pthread_mutex_unlock(inf->lock_dead);

		return 1;
	}
	return 0;
}
void	*must_eat(void *av)
{
	t_info	*inf;
	int		i;
	int		count;

	inf = (t_info *)av;
	if (inf->must_eat == -1)
		return (NULL);
	while (1)
	{
		count = 0;
		i = 0;
		while (i < inf->number_philos)
		{
			pthread_mutex_lock(&inf->filo[i].lock_meal);
			if (inf->filo[i].eat_count >= inf->must_eat)
			{
				count++;
			}
			pthread_mutex_unlock(&inf->filo[i].lock_meal);
			i++;
		}
			pthread_mutex_lock(&inf->filo[i].lock_meal);

		if(must_eat_checking(inf,count))
			return NULL;
		
	}
}
int	main(int ac, char **av)
{
	t_info	*inf;
	int		i;

	if (parse(ac, av))
		return (0);
	inf = malloc(sizeof(t_info));
	init(inf, av);
	create_thread(inf);
	i = 0;
	while (i < inf->number_philos)
		pthread_join(inf->philos[i++], NULL);
	pthread_join(inf->monitor_thread, NULL);
	pthread_join(inf->eat_thread, NULL);
	if (inf->is_dead)
		return (0);
	return (0);
}

