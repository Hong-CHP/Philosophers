/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:44:02 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/26 17:30:13 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_childs_thread(t_table *table, char **argv)
{
	
}

int	center_thread_init_table(t_table *table, char **av)
{
	int	i;

	table->nb_philos = ft_atoi(av[1]);
	if (table->nb_philos <= 0)
		return (1);
	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!table->forks)
	{
		free(table);
		return (1);
	}
	while (i < table->nb_philos)
	{
		pthread_mutex_init(&(table->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(table->log_print), NULL);
	pthread_mutex_init(&(table->life_data), NULL);
	create_childs_thread(table, av);
}

int main(int argc, char **argv)
{
	t_table	*table;
	int	i;
	
	if (argc < 5)
		return (1);
	if (!argv[1][0])
		return (1);
	table = (t_table*)malloc(sizeof(t_table));
	if (!table)
		return (1);
	memset(table, 0, sizeof(t_table));
	center_thread_init_table(table, argv);
	
	return (0);
}
