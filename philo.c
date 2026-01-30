/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokdas <ogokdas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:29:22 by ogokdas           #+#    #+#             */
/*   Updated: 2026/01/30 19:11:37 by ogokdas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	philo_print(philo, philo->id, "has taken fork");
	ms_sleep(philo->info->die_time);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(philo->info->lock_dead);
	philo->info->is_dead = 1;
	pthread_mutex_lock(philo->info->lock_write);
	printf("%llu %d died\n", get_time() - philo->info->start_time, philo->id);
	pthread_mutex_unlock(philo->info->lock_write);
	pthread_mutex_unlock(philo->info->lock_dead);
}

void	routine(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	philo_print(philo, philo->id, "has taken fork");
	pthread_mutex_lock(philo->r_fork);
	philo_print(philo, philo->id, "has taken fork");
	philo_print(philo, philo->id, "is eating");
	pthread_mutex_lock(&philo->lock_meal);
	philo->eat_count++;
	philo->last_meal_time = get_time() - philo->info->start_time;
	pthread_mutex_unlock(&philo->lock_meal);
	ms_sleep(philo->info->eating_time);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo_print(philo, philo->id, "is sleeping");
	ms_sleep(philo->info->time_sleep);
	philo_print(philo, philo->id, "is thinking");
}

void	*to_do(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	if (philo->info->number_philos == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(philo->info->lock_dead);
		if (philo->info->is_dead == 1
			|| philo->info->is_dead == 2)
		{
			pthread_mutex_unlock(philo->info->lock_dead);
			break ;
		}
		pthread_mutex_unlock(philo->info->lock_dead);
		routine(philo);
	}
	return (NULL);
}

void	create_thread(t_info *inf)
{
	int	i;

	i = 0;
	inf->phi = malloc(sizeof(t_philo) * inf->number_philos);
	inf->philos = malloc(sizeof(pthread_t) * inf->number_philos);
	while (i < inf->number_philos)
	{
		inf->phi[i].id = i + 1;
		inf->phi[i].l_fork = &inf->forks[i];
		inf->phi[i].r_fork = &inf->forks[(i + 1)
			% inf->number_philos];
		inf->phi[i].eat_count = 0;
		inf->phi[i].info = inf;
		pthread_mutex_init(&inf->phi[i].lock_meal, NULL);
		inf->phi[i].last_meal_time = inf->start_time;
		pthread_create(&inf->philos[i], NULL,
			to_do, &inf->phi[i]);
		i++;
	}
	pthread_create(&inf->monitor_thread, NULL, is_dead, inf);
	pthread_create(&inf->eat_thread, NULL, must_eat, inf);
}

void	init(t_info *inf, char **av)
{
	int	i;

	inf->number_philos = ft_atoi(av[1]);
	inf->die_time = ft_atoi(av[2]);
	inf->eating_time = ft_atoi(av[3]);
	inf->time_sleep = ft_atoi(av[4]);
	inf->count = 0;
	if (av[5])
		inf->must_eat = ft_atoi(av[5]);
	else
		inf->must_eat = -1;
	inf->is_dead = 0;
	inf->start_time = get_time();
	inf->forks = malloc(sizeof(pthread_mutex_t)
			* inf->number_philos);
	i = 0;
	while (i < inf->number_philos)
		pthread_mutex_init(&inf->forks[i++], NULL);
	inf->lock_write = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(inf->lock_write, NULL);
	inf->lock_dead = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(inf->lock_dead, NULL);
}
