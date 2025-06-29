/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:38:01 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/29 13:26:42 by hporta-c         ###   ########.fr       */
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

void	clean_all(t_table *table, t_params *p_data)
{
	if (p_data)
		free(p_data);
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
	if (table)
		free(table);
}
