/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokdas <ogokdas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:29:22 by ogokdas           #+#    #+#             */
/*   Updated: 2026/01/19 19:09:06 by ogokdas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}
void	philo_print(t_philo *philo, int id, char *str)
{
	pthread_mutex_lock(philo->info->lock_write);
	pthread_mutex_lock(philo->info->lock_dead);
	if (philo->info->is_dead == 0)
		printf("%llu %d %s\n",
			get_time() - philo->info->start_time, id, str);
	pthread_mutex_unlock(philo->info->lock_dead);
	pthread_mutex_unlock(philo->info->lock_write);
}


void *is_dead(void *av)
{
    t_info *inf = (t_info *)av;
    int i;

    i = 0;
    pthread_mutex_lock(inf->lock_dead);
    
    while(1)
    {
        while(i < inf->number_philos)
        {
            if(inf->die_time <= get_time() - inf->filo[i].last_meal_time)
            {
                inf->is_dead = 1;
                printf("%llu %d %s\n",get_time() - inf->start_time, inf->filo[i].id, "died");
                return NULL;
            }    
            i++;
        }
        i = 0;
    }
    pthread_mutex_unlock(inf->lock_dead);
    
}

void *to_do(void *thread)
{
    t_philo *philo = (t_philo *)thread;
    while (1)
    {
		if (philo->info->is_dead)
		{
			break ;
		}

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
        philo_print(philo,philo->id,"has taken fork");
        philo_print(philo,philo->id,"has taken fork");
        philo_print(philo,philo->id,"is eating");
        usleep(philo->info->eating_time * 1000);
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
        philo->last_meal_time = get_time();
        philo_print(philo,philo->id,"is sleeping");
       //usleep(philo->info->time_sleep * 1000);
        philo_print(philo,philo->id,"is thinking");
    }
    return NULL;
}

void create_thread(t_info *inf)
{
    int i = 0;
    inf->filo = malloc(sizeof(t_philo) * inf->number_philos);
    inf->philos = malloc(sizeof(pthread_t) * inf->number_philos);
    while (i < inf->number_philos)
    {
        inf->filo[i].id = i + 1;
        inf->filo[i].l_fork = &inf->forks[i];
        inf->filo[i].r_fork = &inf->forks[(i + 1) % inf->number_philos];
        inf->filo[i].last_meal_time = inf->start_time;
        inf->filo[i].info = inf;
        pthread_create(&inf->philos[i], NULL, to_do, &inf->filo[i]);
        i++;
    }
    pthread_create(&inf->monitor_thread, NULL, is_dead, inf);
}

void init(t_info *inf, char **av)
{

    inf->number_philos = ft_atoi(av[1]);
    inf->die_time = ft_atoi(av[2]);
    inf->eating_time = ft_atoi(av[3]);
    inf->time_sleep = ft_atoi(av[4]);
    inf->is_dead=0;
    inf->start_time = get_time();
    inf->forks = malloc(sizeof(pthread_mutex_t) * inf->number_philos);
    int i = 0;

    while (i < inf->number_philos)
    {
        pthread_mutex_init(&inf->forks[i], NULL);
        i++; 
    }

    inf->lock_write = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(inf->lock_write, NULL);
    inf->lock_dead = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(inf->lock_dead,NULL);
}

int main(int ac, char **av)
{
    if(parse(ac,av))
        return 0;
    t_info *inf = malloc(sizeof(t_info ));
    init(inf, av);
    create_thread(inf);

    int i = -1;

    while (++i < inf->number_philos)
        pthread_join(inf->philos[i], NULL);
    pthread_join(inf->monitor_thread,NULL);
    if (inf->is_dead)
        return 1;
}
