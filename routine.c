/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:38:14 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/02 17:43:48 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	print_routine(philo, "is thinking");
	usleep(1000);
}

int	take_first_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right);
	else
		pthread_mutex_lock(philo->left);
	pthread_mutex_lock(&(philo->table->life_data));
	if (philo->table->death == 1)
	{
		if (philo->id % 2 == 0)
			pthread_mutex_unlock(philo->right);
		else
			pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(&(philo->table->life_data));
		return (0);
	}
	pthread_mutex_unlock(&(philo->table->life_data));
	print_routine(philo, "has taken a fork");
	return (1);
}

int	take_second_fork(t_philo *philo)
{
	if (philo->table->nb_philos == 1)
		return (0);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->left);
	else
		pthread_mutex_lock(philo->right);
	pthread_mutex_lock(&(philo->table->life_data));
	if (philo->table->death == 1)
	{
		if (philo->id % 2 == 0)
			pthread_mutex_unlock(philo->left);
		else
			pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(&(philo->table->life_data));
		return (0);
	}
	pthread_mutex_unlock(&(philo->table->life_data));
	print_routine(philo, "has taken a fork");
	return (1);
}

int	take_forks_and_eating(t_philo *philo)
{
	if (!take_forks_successed(philo))
		return (0);
	pthread_mutex_lock(&(philo->table->life_data));
	if (philo->table->death == 1)
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(&(philo->table->life_data));	
		return (0);
	}
	philo->last_eat = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&(philo->table->life_data));
	print_routine(philo, "is eating");
	action_duration(philo, philo->table->data->eat_t);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	return (1);
}

void	sleeping(t_philo *philo)
{
	print_routine(philo, "is sleeping");
	action_duration(philo, philo->table->data->time_to_sleep);
}
