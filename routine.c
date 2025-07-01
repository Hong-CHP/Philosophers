/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:38:14 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/01 17:23:41 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_routine(t_philo *philo, char *msg)
{
    long long   timestamp;
    
    pthread_mutex_lock(&(philo->table->log_print));
    timestamp = get_time() - philo->table->start_time;
    printf("%lld %d %s\n", timestamp, philo->id, msg);
    pthread_mutex_unlock(&(philo->table->log_print));
}

void	thinking(t_philo *philo)
{
	print_routine(philo, "is thinking");
	usleep(1000);
}

void	take_forks_and_eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->left));
		print_routine(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->right));
		print_routine(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(philo->right));
		print_routine(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->left));
		print_routine(philo, "has taken a fork");
	}
	pthread_mutex_lock(&(philo->table->life_data));
	philo->last_eat = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&(philo->table->life_data));
	print_routine(philo, "is eating");
	usleep(philo->table->p_data->time_to_eat * 1000);
	pthread_mutex_unlock(&(philo->left));
	pthread_mutex_unlock(&(philo->right));
}

void	sleeping(t_philo *philo)
{
	print_routine(philo, "is sleeping");
	usleep(philo->table->p_data->time_to_sleep * 1000);
}

int still_alive(t_philo *philo)
{
	long long   now;
	
	pthread_mutex_lock(&(philo->table->life_data));
	if (philo->table->death)
	{
		pthread_mutex_unlock(&(philo->table->life_data));		
		return (0);		
	}
	now = get_time();
	if (now - philo->last_eat >= philo->table->p_data->time_to_die)
	{
		pthread_mutex_unlock(&(philo->table->life_data));		
		return (0);
	}
	if (philo->table->p_data->nb_times_of_eat != 0
		&& philo->eat_count == philo->table->p_data->nb_times_of_eat)
	{
		pthread_mutex_unlock(&(philo->table->life_data));
		return (0);
	}
	pthread_mutex_unlock(&(philo->table->life_data));
	return (1);
}
