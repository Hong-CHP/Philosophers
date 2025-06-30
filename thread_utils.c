/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:14:20 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/30 17:52:00 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (err != 0)
		init_mutex_error(table, i, log_creat, life_creat);
	log_creat = 1;
	err = pthread_mutex_init(&(table->life_data), NULL);
	if (err != 0)
		init_mutex_error(table, i, log_creat, life_creat);
	life_creat = 1;
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

void    print_routine(t_philo *philo, char *msg)
{
    long long   timestamp;
    
    pthread_mutex_lock(&(philo->table->log_print));
    timestamp = get_time() - philo->table->start_time;
    printf("%lld %d %s\n", timestamp, philo->id, msg);
    pthread_mutex_unlock(&(philo->table->log_print));
}