# ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>

typedef struct s_info
{
    int number_philos;
    int eating_time;
    int die_time;
    int time_sleep;
    int is_dead;
    pthread_t *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t *lock_write;
    struct s_philo *filo;
    
} t_info;

typedef struct s_philo
{
    int id;
    int eat_count;
    int last_meal_time;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    struct s_info *info;

    
}t_philo ;


int	ft_atoi(const char *nptr);


#endif