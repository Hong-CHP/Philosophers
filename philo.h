/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:44:17 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/02 17:41:01 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct	s_table t_table;
typedef struct	s_philo t_philo;

typedef struct	s_params
{
	long long	die_t;
	long long	eat_t;
	long long	time_to_sleep;
	int			nb_times_of_eat;
}				t_params;

typedef struct	s_table
{
	int				nb_philos;
	long long 		start_time;
	int				death;
	t_params		*data;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	log_print;
	pthread_mutex_t	life_data;
}					t_table;

typedef	struct	s_philo
{
	int				id;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	long long		last_eat;
	int				eat_count;
	t_table 		*table;
}					t_philo;

void	ft_putstr(char *str);
long long	ft_atoi(char *str);
long long	get_time(void);
t_params	*get_val_from_params(char **av);
void	clean_all(t_table *table);
void	init_mutex(t_table *table);
int		create_thread_error(void);
int		lock_unlock_life_if_death(t_philo *philo);
void	destory_mutex(t_table *table);
void	if_only_one_philo(t_philo *philo);
int		take_forks_successed(t_philo *philo);
void	action_duration(t_philo *philo, long long duration);
int		still_alive(t_philo *philo);
void	print_routine(t_philo *philo, char *msg);
void	*philo_routine(void *args);
void	thinking(t_philo *philo);
int		take_forks_and_eating(t_philo *philo);
void	sleeping(t_philo *philo);
int		everybd_ate_enough(t_table *control);
void	*death_control(void *args);

#endif