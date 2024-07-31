/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:03:49 by mel-bouh          #+#    #+#             */
/*   Updated: 2024/07/29 01:42:18 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_error(t_inst *in)
{
	pthread_mutex_lock(&in->death_lock);
	in->death = 1;
	pthread_mutex_unlock(&in->death_lock);
}

int	print_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		write (2, &str[len++], 1);
	return (0);
}

size_t	get_current_time(void)
{
	t_timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	checkarg(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (!s[i])
		return (0);
	return (1);
}

long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	number;

	i = 0;
	sign = 1;
	number = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (number * sign);
}
