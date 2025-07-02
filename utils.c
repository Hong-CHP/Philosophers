/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:38:01 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/02 16:37:46 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr(char *str)
{
	while(*str)
		write(1, str++, 1);
}

long long	ft_atoi(char *str)
{
	int	i;
	long long	flag;
	long long	nb;
	
	flag = 1;
	i = 0;
	while(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			flag *= -1;
		i++;
	}
	nb = 0;
	while (str[i])
	{
		nb = nb * 10;
		nb = nb + str[i] - '0';
		i++;
	}
	return (nb * flag);
}

long long	get_time(void)
{
	struct timeval actual;
	
	gettimeofday(&actual, NULL);
	return (actual.tv_sec * 1000 + actual.tv_usec / 1000);
}

t_params	*get_val_from_params(char **av)
{	
	t_params	*data;
	
	if (!av[1] || !av[2] || !av[3] || !av[4])
		return (NULL);
	data = (t_params*)malloc(sizeof(t_params));
	if (!data)
		return (NULL);
	memset(data, 0, sizeof(t_params));
	data->die_t = ft_atoi(av[2]);
	data->eat_t = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5] != NULL)
		data->nb_times_of_eat = (int)ft_atoi(av[5]);
	if (data->die_t <= 0 || data->eat_t <= 0
		|| data->time_to_sleep <= 0)
		return (NULL);
	if (av[5] && av[5][0] != '\0' && data->nb_times_of_eat < 0)
		return (NULL);
	return (data);
}

void	clean_all(t_table *table)
{
	if (table->data)
		free(table->data);
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
	if (table)
		free(table);
}
