/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_childs_thread.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:59:49 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/01 17:22:43 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (still_alive(philo))
	{
		thinking(philo);
		take_forks_and_eating(philo);
		sleeping(philo);
	}
	return (NULL);
}

int		everybd_ate_enough(t_table *control)
{
	int	i;

	i = 0;
	if (control->p_data->nb_times_of_eat == 0)
		return (0);
	while (i < control->nb_philos)
	{
		pthread_mutex_lock(&(control->life_data));
		if (control->philos[i].eat_count < control->p_data->nb_times_of_eat)
		{
			pthread_mutex_unlock(&(control->life_data));
			return (0);
		}
		pthread_mutex_unlock(&(control->life_data));
		i++;
	}
	return (1);
}

int     checker_nb_times_of_eat(t_table *control)
{
    if (everybd_ate_enough(control))
	{
		pthread_mutex_lock(&(control->life_data));
		control->death = 1;
		pthread_mutex_unlock(&(control->life_data));
		return (0);
	}
    return (1);
}

void	*death_control(void *args)
{
	t_table *control;
	int	i;

	control = (t_table *)args;
	while (1)
	{
		i = 0;
		while (i < control->nb_philos)
		{
			pthread_mutex_lock(&(control->life_data));
			if (!control->death && get_time() - control->philos[i].last_eat >= control->p_data->time_to_die)
			{
				print_routine(&(control->philos[i]), "died");
				control->death = 1;
				pthread_mutex_unlock(&(control->life_data));
				return (NULL);
			}
			i++;
		}
        if (!checker_nb_times_of_eat(control))
            return (NULL);
		usleep(1000);
	}
	return (NULL);
}
