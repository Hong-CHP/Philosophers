/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:44:17 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/27 16:27:54 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct	s_params
{
	int			nb_of_philos;
	long long	time_to_eat;
	long long	time_to_die;
	long long	time_to_sleep;
	int			nb_times_of_eat;
}				t_params;

typedef struct	s_table
{
	int				nb_philos;
	long long 		start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
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

int	ft_atoi(char *str);
long long	get_time(void);

#endif