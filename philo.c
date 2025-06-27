/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:44:02 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/27 16:31:54 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_childs_thread(t_table *table, char **argv)
{
	
}

void	init_philo(t_table *table, char **av)
{
	int	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (!table->philos)
	{
		free(table);
		return ;
	}
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
		free(table->philos);
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
	init_philo(table, av);
	create_childs_thread(table, av);
}

t_params	*get_val_from_params(int ac, char **av)
{
	int	i;
	int	j;
	
	i = 1;
	while(i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			
			j++;
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	t_table	*table;
	
	if (argc < 5)
		return (1);

	table = (t_table*)malloc(sizeof(t_table));
	if (!table)
		return (1);
	memset(table, 0, sizeof(t_table));
	center_thread_init_table(table, argv);

	return (0);
}
