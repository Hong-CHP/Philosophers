/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_childs_thread.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:59:49 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/03 15:38:42 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_routine(t_philo *philo, char *msg)
{
    long long   timestamp;
    
    pthread_mutex_lock(&(philo->table->log_print));
    timestamp = get_time() - philo->table->start_time;
    printf("%lldms %d %s\n", timestamp, philo->id, msg);
    pthread_mutex_unlock(&(philo->table->log_print));
}

void	*philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (still_alive(philo))
	{
		if (lock_unlock_life_if_death(philo))
			break ;
		thinking(philo);
		if (lock_unlock_life_if_death(philo))
			break ;
		if (!take_forks_and_eating(philo))
			break ;
		if (lock_unlock_life_if_death(philo))
			break ;
		sleeping(philo);
	}
	return (NULL);
}

int		everybd_ate_enough(t_table *control)
{
	int	i;

	i = 0;
	if (control->data->nb_times_of_eat == 0)
		return (0);
	while (i < control->nb_philos)
	{
		pthread_mutex_lock(&(control->life_data));
		if (control->philos[i].eat_count < control->data->nb_times_of_eat)
		{
			pthread_mutex_unlock(&(control->life_data));
			return (0);
		}
		pthread_mutex_unlock(&(control->life_data));
		i++;
	}
	return (1);
}

int	update_hungry_death_info(t_table *cntl)
{
	int	i;

	i = 0;
	while (i < cntl->nb_philos)
	{
		pthread_mutex_lock(&(cntl->life_data));
		if (!cntl->death
			&& get_time() - cntl->philos[i].last_eat >= cntl->data->die_t)
		{
			print_routine(&(cntl->philos[i]), "died");
			cntl->death = 1;
			pthread_mutex_unlock(&(cntl->life_data));
			return (1);
		}
		pthread_mutex_unlock(&(cntl->life_data));
		i++;
	}
	return (0);
}

void	*death_control(void *args)
{
	t_table *cntl;

	cntl = (t_table *)args;
	while (1)
	{
		if (update_hungry_death_info(cntl))
			return (NULL);
    	if (everybd_ate_enough(cntl))
		{
			pthread_mutex_lock(&(cntl->life_data));
			cntl->death = 1;
			pthread_mutex_unlock(&(cntl->life_data));
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
