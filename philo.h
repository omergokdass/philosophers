# ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
    int id;
    long long last_meal_time;
    int eat_count;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    pthread_mutex_t lock_meal;
    struct s_info *info;

}t_philo ;

typedef struct s_info
{
    int number_philos;
    int eating_time;
    int die_time;
    int time_sleep;
    int is_dead;
    int must_eat;
    int count;
    long long start_time;
    pthread_t *philos;
    pthread_t monitor_thread;
    pthread_t eat_thread;

    
    pthread_mutex_t *forks;
    pthread_mutex_t *lock_write;
    pthread_mutex_t *lock_dead;
    t_philo *filo;
} t_info;

int	ft_atoi(const char *nptr);
int parse (int ac, char **av);

#endif