/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:50:03 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/03 15:15:45 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks_successed(t_philo *philo)
{
	if (!take_first_fork(philo))
		return (0);
	if (!take_second_fork(philo))
	{
		if (philo->id % 2 == 0)
			pthread_mutex_unlock(philo->right);
		else
			pthread_mutex_unlock(philo->left);
		return (0);
	}
	return (1);
}

void	action_duration(t_philo *philo, long long duration)
{
	long long	start_po;

	start_po = get_time();
	while (get_time() - start_po < duration)
	{
		if(lock_unlock_life_if_death(philo))
			break ;
		usleep(100);
	}
}

int still_alive(t_philo *philo)
{
	long long   now;
	
	pthread_mutex_lock(&(philo->table->life_data));
	if (philo->table->death == 1)
	{
		pthread_mutex_unlock(&(philo->table->life_data));
		return (0);
	}
	now = get_time();
	if (now - philo->last_eat >= philo->table->data->die_t)
	{
		pthread_mutex_unlock(&(philo->table->life_data));		
		return (0);
	}
	if (philo->table->data->nb_times_of_eat != 0
		&& philo->eat_count == philo->table->data->nb_times_of_eat)
	{
		pthread_mutex_unlock(&(philo->table->life_data));
		return (0);
	}
	pthread_mutex_unlock(&(philo->table->life_data));
	return (1);
}
