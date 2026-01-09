# ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>

typedef struct s_philo
{
    int id;
    int last_meal_time;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    struct s_info *info;

}t_philo ;

typedef struct s_info
{
    int number_philos;
    int eating_time;
    int die_time;
    int time_sleep;
    int must_eat;
    int eat_count;
    int is_dead;
    pthread_t *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t *lock_write;
    t_philo *filo;
} t_info;



int	ft_atoi(const char *nptr);


#endif