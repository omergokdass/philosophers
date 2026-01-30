/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokdas <ogokdas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:52:34 by ogokdas           #+#    #+#             */
/*   Updated: 2026/01/30 16:09:24 by ogokdas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all(t_info *inf)
{
	int	i;

	i = 0;
	while (i < inf->number_philos)
	{
		pthread_mutex_destroy(&inf->forks[i]);
		pthread_mutex_destroy(&inf->phi[i].lock_meal);
		i++;
	}
	pthread_mutex_destroy(inf->lock_write);
	pthread_mutex_destroy(inf->lock_dead);
	free(inf->forks);
	free(inf->phi);
	free(inf->philos);
	free(inf->lock_write);
	free(inf->lock_dead);
	free(inf);
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
	destroy_all(inf);
	return (0);
}
