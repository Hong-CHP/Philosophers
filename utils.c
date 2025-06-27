/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:38:01 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/27 16:18:07 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	flag;
	int	nb;
	
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