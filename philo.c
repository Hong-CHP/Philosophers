/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:44:02 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/30 17:59:04 by hporta-c         ###   ########.fr       */
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

void	create_childs_thread(t_table *table, char **argv)
{
	int	i;
	pthread_t	*philosof;

	philosof = malloc(sizeof(pthread_t) * table->nb_philos);
	if (!philosof)
	{
		clean_all(table);
		return ;
	}
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_create(&philosof[i], NULL, philo_routine, &(table->philos[i]));
		i++;
	}
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(philosof[i], NULL);
		i++;
	}
	free(philosof);
}

int	init_philo(t_table *table, char **av)
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
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!table->forks)
	{
		free(table);
		return (1);
	}
	// 初始叉子锁， 打印锁和生命锁, 初始锁失败直接clean & exit
	init_mutex(table);
	if (init_philo(table, av) != 0)
	{
		destory_mutex(table);
		return (1);
	}
	create_childs_thread(table, av);
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
