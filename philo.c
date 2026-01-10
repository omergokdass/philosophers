/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokdas <ogokdas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:29:22 by ogokdas           #+#    #+#             */
/*   Updated: 2026/01/10 16:37:48 by ogokdas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *to_do(void *thread)
{
    t_philo *philo = (t_philo *)thread;
    while (1)
    {
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(philo->l_fork);
            pthread_mutex_lock(philo->r_fork);
        }
        else
        {
            pthread_mutex_lock(philo->r_fork);                                                                                                                            
            pthread_mutex_lock(philo->l_fork);
        }

        pthread_mutex_lock(philo->info->lock_write);
        printf("llu %d has taken a fork\n", philo->id);
        printf("llu %d has taken a fork\n", philo->id);
        pthread_mutex_unlock(philo->info->lock_write);

        // eating coming...
        pthread_mutex_lock(philo->info->lock_write);
        printf("llu %d is eating\n", philo->id);
        pthread_mutex_unlock(philo->info->lock_write);


        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);

        usleep(philo->info->time_sleep * 1000);
        pthread_mutex_lock(philo->info->lock_write);
        printf("llu %d is sleeping\n", philo->id);
        pthread_mutex_unlock(philo->info->lock_write);
        
        pthread_mutex_lock(philo->info->lock_write);
        printf("llu %d is thinking\n", philo->id);
        pthread_mutex_unlock(philo->info->lock_write);
    }
    return NULL;
}

void create_thread(t_info *asd)
{
    int i = 0;
    asd->filo = malloc(sizeof(t_philo) * asd->number_philos);
    asd->philos = malloc(sizeof(pthread_t) * asd->number_philos);
    while (i < asd->number_philos)
    {
        asd->filo[i].id = i + 1;
        asd->filo[i].l_fork = &asd->forks[i];
        asd->filo[i].r_fork = &asd->forks[(i + 1) % asd->number_philos];
        asd->filo[i].info = asd;
        pthread_create(&asd->philos[i], NULL, to_do, &asd->filo[i]);
        i++;
    }
}

void init(t_info *inf, char **av)
{

    inf->number_philos = ft_atoi(av[1]);
    inf->die_time = ft_atoi(av[2]);
    inf->eating_time = ft_atoi(av[3]);
    inf->time_sleep = ft_atoi(av[4]);
    inf->is_dead=0;
    inf->forks = malloc(sizeof(pthread_mutex_t) * inf->number_philos);
    int i = 0;

    while (i < inf->number_philos)
    {
        pthread_mutex_init(&inf->forks[i], NULL);
        i++; 
    }

    inf->lock_write = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(inf->lock_write, NULL);
}

int main(int ac, char **av)
{
    if(parse(ac,av))
        return 0;
    t_info *inf = malloc(sizeof(t_info ));
    init(inf, av);
    create_thread(inf);

    int i = 0;

      while (i < inf->number_philos)
      {
          pthread_join(inf->philos[i], NULL);
          i++;
      }
} 