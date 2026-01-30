/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokdas <ogokdas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:55:55 by ogokdas           #+#    #+#             */
/*   Updated: 2026/01/30 16:07:16 by ogokdas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_info	t_info;

typedef struct s_philo
{
	int				id;
	long long		last_meal_time;
	int				eat_count;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	lock_meal;
	t_info			*info;
}	t_philo;

typedef struct s_info
{
	int				number_philos;
	int				eating_time;
	int				die_time;
	int				time_sleep;
	int				is_dead;
	int				must_eat;
	int				count;
	long long		start_time;
	pthread_t		*philos;
	pthread_t		monitor_thread;
	pthread_t		eat_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock_write;
	pthread_mutex_t	*lock_dead;
	t_philo			*phi;
}	t_info;

int			ft_atoi(const char *nptr);
int			parse(int ac, char **av);
long long	get_time(void);
void		ms_sleep(int time);
void		philo_print(t_philo *philo, int id, char *str);
void		create_thread(t_info *inf);
void		init(t_info *inf, char **av);
int			is_hungry(t_info *inf, int i);
void		*is_dead(void *av);
void		*to_do(void *thread);
void		*must_eat(void *av);

#endif
