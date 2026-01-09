#include "philo.h"
void *to_do(void *asd)
{
    t_philo *inf = (t_philo *)asd;
    while (1)
    {
        if (inf->id % 2 == 0)
        {
            pthread_mutex_lock(inf->l_fork);
            printf("llu %d has taken a fork\n", inf->id);
            pthread_mutex_lock(inf->r_fork);
            printf("llu %d has taken a fork\n", inf->id);
        }
        else
        {
            pthread_mutex_lock(inf->r_fork);
            printf("llu %d has taken a fork\n", inf->id);
            pthread_mutex_lock(inf->l_fork);
            printf("llu %d has taken a fork\n", inf->id);
        }
        printf("llu %d is eating", inf->id);
        pthread_mutex_unlock(inf->l_fork);
        pthread_mutex_unlock(inf->r_fork);
        printf("llu %d is sleeping", inf->id);
        usleep(inf->info->time_sleep * 1000);
        printf("llu %d is thinking", inf->id);
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
    inf->forks = malloc(sizeof(pthread_mutex_t) * inf->number_philos);
    int i = 0;

    while (i < inf->number_philos)
    {
        pthread_mutex_init(&inf->forks[i], NULL);
        i++; 
    }
}

int main(int ac, char **av)
{
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