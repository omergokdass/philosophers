#include "philo.h"

void *to_do(void *asd)
{

}
void create_thread(t_info *asd)
{
    int i = 0;
    while(i<asd->number_philos)
    {   
        
        pthread_create(asd->philos[i],NULL, to_do, asd->filo);
        i++;
    }

}
void init(t_info *inf, char **av)
{
    
    inf->number_philos = ft_atoi(av[1]);
    inf->die_time = ft_atoi(av[2]);
    inf->eating_time = ft_atoi(av[3]);
    inf->time_sleep = ft_atoi(av[4]);

    int i = 0;
    while(i < inf->number_philos)
    {
        // i will create fork 
        i++;
    }

}
int main(int ac, char **av)
{
    t_info *inf = malloc(sizeof(t_info*));
    init(inf,av);

    int i = 0;

}