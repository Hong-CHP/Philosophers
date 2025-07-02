/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:14:20 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/02 16:18:35 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_unlock_life_if_death(t_philo *philo)
{
	pthread_mutex_lock(&(philo->table->life_data));
	if (philo->table->death == 1)
	{
		pthread_mutex_unlock(&(philo->table->life_data));	
		return (1);
	}
	pthread_mutex_unlock(&(philo->table->life_data));
	return (0);
}

int	create_thread_error(void)
{
	printf("Thread create failed");
	return (0);	
}

void	init_mutex_error(t_table *table, int idx, int log_creat, int life_creat)
{
	write(2, "Mutex init failed\n", 19);
	while (idx >= 0)
	{
		pthread_mutex_destroy(&(table->forks[idx]));
		idx--;
	}
	if (log_creat)
		pthread_mutex_destroy(&(table->log_print));
	if (life_creat)
		pthread_mutex_destroy(&(table->life_data));
	clean_all(table);
	exit(EXIT_FAILURE);
}

void	init_mutex(t_table *table)
{
	int	i;
	int err;
	int log_creat;
	int	life_creat;

	log_creat = 0;
	life_creat = 0;
	i = 0;
	while (i < table->nb_philos)
	{
		err = pthread_mutex_init(&(table->forks[i]), NULL);
		if (err != 0)
			init_mutex_error(table, i, log_creat, life_creat);
		i++;
	}
	err = pthread_mutex_init(&(table->log_print), NULL);
	log_creat = 1;
	if (err != 0)
		init_mutex_error(table, i, log_creat, life_creat);
	err = pthread_mutex_init(&(table->life_data), NULL);
	life_creat = 1;
	if (err != 0)
		init_mutex_error(table, i, log_creat, life_creat);
}

void	destory_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&(table->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(table->log_print));
	pthread_mutex_destroy(&(table->life_data));
}

