/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:44:02 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/01 17:52:22 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_childs_thread(pthread_t *philosof, pthread_t *cntrl, t_table *t)
{
	int	i;

	pthread_create(cntrl, NULL, death_control, t);
	i = 0;
	while (i < t->nb_philos)
	{
		pthread_create(&philosof[i], NULL, philo_routine, &(t->philos[i]));
		i++;
	}
	pthread_join(cntrl, NULL);
	i = 0;
	while (i < t->nb_philos)
	{
		pthread_join(philosof[i], NULL);
		i++;
	}
}

int	childs_thread(t_table *table)
{
	int	i;
	pthread_t	*philosof;
	pthread_t	*controller;

	philosof = malloc(sizeof(pthread_t) * table->nb_philos);
	if (!philosof)
		return (1);
	controller = malloc(sizeof(pthread_t));
	if (!controller)
	{
		free(philosof);
		return (1);
	}
	create_childs_thread(philosof, controller, table);
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
		table->philos[i].last_eat = get_time();
		table->philos[i].eat_count = 0; 
		table->philos[i].table = table; 
		i++;
	}
	return (0);
}

int	center_thread_init_table(t_table *table, char **av)
{
	table->nb_philos = (int)ft_atoi(av[1]);
	if (table->nb_philos <= 0)
		return (1);
	//初始时间
	table->start_time = get_time();
	table->death = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!table->forks)
		return (1);
	// 初始叉子锁， 打印锁和生命锁, 初始锁失败直接clean & exit
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
	table->p_data = get_val_from_params(argv);
	if (!table->p_data)
	{
		ft_putstr("Parameter no vailable\n");
		free(table);
		return (1);
	}
	// printf("params_val = %d, %lld, %lld, %lld, %d\n", p_data->nb_of_philos, p_data->time_to_die, p_data->time_to_eat, p_data->time_to_sleep, p_data->nb_times_of_eat);
	if (center_thread_init_table(table, argv) != 0)
	{
		clean_all(table);
		return (1);
	}
	clean_all(table);
	return (0);
}
