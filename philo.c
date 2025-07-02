/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:44:02 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/02 17:39:45 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_childs_thread(pthread_t *phil, pthread_t *cntrl, t_table *t)
{
	int	i;
	int	res_p;
	int	res_c;

	res_c = pthread_create(cntrl, NULL, death_control, t);
	if (res_c != 0)
		return (create_thread_error());
	i = 0;
	while (i < t->nb_philos)
	{
		res_p = pthread_create(&phil[i], NULL, philo_routine, &(t->philos[i]));
		if (res_p != 0)
			return (create_thread_error());
		i++;
	}
	i = 0;
	while (i < t->nb_philos)
	{
		pthread_join(phil[i], NULL);
		i++;
	}
	pthread_join(*cntrl, NULL);
	return (1);
}

int	childs_thread(t_table *table)
{
	int	i;
	pthread_t	*controller;
	pthread_t	*philosof;

	philosof = malloc(sizeof(pthread_t) * table->nb_philos);
	if (!philosof)
		return (1);
	controller = malloc(sizeof(pthread_t));
	if (!controller)
	{
		free(philosof);
		return (1);
	}
	if (!create_childs_thread(philosof, controller, table))
		return (1);
	free(philosof);
	free(controller);
	return (0);
}

int	init_philo(t_table *table)
{
	int	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (!table->philos)
		return (1);
	while (i < table->nb_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].left = &(table->forks[i]);
		table->philos[i].right = &(table->forks[(i + 1) % table->nb_philos]);
		table->philos[i].last_eat = table->start_time;
		table->philos[i].eat_count = 0; 
		table->philos[i].table = table; 
		i++;
	}
	return (0);
}

int	center_thread_init_table(t_table *table)
{
	table->start_time = get_time();
	table->death = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!table->forks)
		return (1);
	init_mutex(table);
	if (init_philo(table) != 0)
	{
		destory_mutex(table);
		return (1);
	}
	if (childs_thread(table) != 0)
	{
		destory_mutex(table);
		return (1);
	}
	destory_mutex(table);
	return (0);
}

int main(int argc, char **argv)
{
	t_table		*table;
	
	if (argc < 5)
		return (1);
	table = (t_table*)malloc(sizeof(t_table));
	if (!table)
		return (1);
	memset(table, 0, sizeof(t_table));
	table->nb_philos = (int)ft_atoi(argv[1]);
	if (table->nb_philos <= 0)
		return (1);
	table->data = get_val_from_params(argv);
	if (!table->data)
	{
		ft_putstr("Parameter no vailable\n");
		free(table);
		return (1);
	}
	if (center_thread_init_table(table) != 0)
	{
		clean_all(table);
		return (1);
	}
	clean_all(table);
	return (0);
}
