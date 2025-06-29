/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:44:02 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/29 13:32:09 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *args)
{
	
}

int	create_childs_thread(t_table *table, t_params *p_data, char **argv)
{
	int	i;
	pthread_t	*philosof;

	philosof = malloc(sizeof(pthread_t) * table->nb_philos);
	if (!philosof)
	{
		clean_all(table, p_data);
		return (-1);
	}
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_create(&philosof[i], NULL, philo_routine, table);
		i++;
	}
	return (0);
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

int	center_thread_init_table(t_table *table, t_params *p_data, char **av)
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
	create_childs_thread(table, p_data, av);
	return (0);
}

t_params	*get_val_from_params(char **av)
{	
	t_params	*p_data;
	
	p_data = (t_params*)malloc(sizeof(t_params));
	if (!p_data)
		return (NULL);
	memset(p_data, 0, sizeof(t_params));
	p_data->nb_of_philos = (int)ft_atoi(av[1]);
	p_data->time_to_die = ft_atoi(av[2]);
	p_data->time_to_eat = ft_atoi(av[3]);
	p_data->time_to_sleep = ft_atoi(av[4]);
	if (av[5] != NULL)
		p_data->nb_times_of_eat = (int)ft_atoi(av[5]);
	if (p_data->nb_of_philos <= 0 || p_data->time_to_die <= 0
		|| p_data->time_to_eat <= 0 || p_data->time_to_sleep <= 0)
		return (NULL);
	if (av[5] && av[5][0] != '\0' && p_data->nb_times_of_eat < 0)
		return (NULL);
	return (p_data);
}

int main(int argc, char **argv)
{
	t_table		*table;
	t_params	*p_data;
	
	if (argc < 5)
		return (1);
	p_data = get_val_from_params(argv);
	if (!p_data)
	{
		ft_putstr("Parameter no vailable\n");
		return (1);
	}
	// printf("params_val = %d, %lld, %lld, %lld, %d\n", p_data->nb_of_philos, p_data->time_to_die, p_data->time_to_eat, p_data->time_to_sleep, p_data->nb_times_of_eat);
	table = (t_table*)malloc(sizeof(t_table));
	if (!table)
	{
		free(p_data);
		return (1);
	}
	memset(table, 0, sizeof(t_table));
	center_thread_init_table(table, p_data, argv);
	
	return (0);
}
