/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:35:27 by mel-bouh          #+#    #+#             */
/*   Updated: 2024/07/29 00:57:03 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_instructions(t_inst *in, int ac)
{
	if (in->tdie < 60 || in->teat < 60 || in->tsleep < 60)
	{
		printf("i am here\n");
		return (print_error("All the timers should be at least 60 ms\n"));
	}
	if (ac == 6 && in->nmeals < 1)
		return (print_error("Invalid number of meals\n"));
	return (1);
}

int	ft_checkchar(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9') && s[i] != 32 \
		&& s[i] != '-' && s[i] != '+')
			return (0);
		if ((s[i] == '-' || s[i] == '+') && \
		!(s[i + 1] >= '0' && s[i + 1] <= '9'))
			return (0);
		if (i != 0 && (s[i] == '-' || s[i] == '+') && s[i - 1] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	ft_checkint(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && s[i] == '0')
		i++;
	while (s[i++])
		j++;
	if (j > 10)
		return (0);
	return (1);
}

int	check_argument(int ac, char **av)
{
	int		i;
	long	nb;

	if (ac < 5 || ac > 6)
		return (print_error("Insuffisant number of arguments\n"));
	i = 1;
	while (i < ac)
	{
		if (!checkarg(av[i]) || !ft_checkchar(av[i]))
			return (print_error("Invalid argument\n"));
		i++;
	}
	i = 1;
	while (i < ac)
	{
		nb = ft_atoi(av[i]);
		if (!ft_checkint(av[i]) || nb > INT_MAX || nb < INT_MIN)
			return (print_error("Invalid int\n"));
		i++;
	}
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
		return (print_error("Philosophers number error\n"));
	if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
		return (print_error("All timer should at least be 60ms\n"));
	return (1);
}
