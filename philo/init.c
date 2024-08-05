/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:32:41 by mel-bouh          #+#    #+#             */
/*   Updated: 2024/08/05 10:14:16 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_fork *f, t_fork *m, t_inst *in)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&in->print, NULL))
		return (print_error("The mutex initialization has failed\n"));
	if (pthread_mutex_init(&in->death_lock, NULL))
		return (print_error("The mutex initialization has failed\n"));
	while (i < in->nphilo)
	{
		if (pthread_mutex_init(&f[i], NULL))
			return (print_error("The mutex initialization has failed\n"));
		if (pthread_mutex_init(&m[i], NULL))
			return (print_error("The mutex initialization has failed\n"));
		i++;
	}
	return (1);
}

int	init_threads(t_philo *p, t_inst *in)
{
	int	i;

	i = 0;
	if (pthread_create(&in->monitor, NULL, monitoring, p))
	{
		set_error(in);
		return (print_error("The threads creations has failed\n"));
	}
	while (i < in->nphilo)
	{
		if (pthread_create(&p[i].th, NULL, routine, &p[i]))
		{
			set_error(in);
			return (print_error("The threads creation process has failed\n"));
		}
		i++;
	}
	return (1);
}

void	fill_instructions(t_inst *in, int ac, char **av)
{
	int	i;

	i = 0;
	in->nphilo = ft_atoi(av[1]);
	in->tdie = ft_atoi(av[2]);
	in->teat = ft_atoi(av[3]);
	in->tsleep = ft_atoi(av[4]);
	in->full = 0;
	in->death = 0;
	in->start = get_current_time();
	if (ac == 5)
		in->nmeals = -1;
	else if (ac == 6)
		in->nmeals = ft_atoi(av[5]);
	while (i <= in->nphilo)
		in->counter[i++] = 0;
}

void	fill_philos(t_philo *p, t_fork *m, t_inst *in, t_fork *f)
{
	int	i;

	i = 0;
	while (i < in->nphilo)
	{
		p[i].id = i + 1;
		p[i].lastmeal = get_current_time();
		p[i].eating = 0;
		p[i].full = 0;
		p[i].turn = 0;
		p[i].meal_lock = &m[i];
		if (i == in->nphilo - 1)
		{
			p[i].rfork = &f[0];
			p[i].lfork = &f[i];
		}
		else
		{
			p[i].rfork = &f[i];
			p[i].lfork = &f[(i + 1) % in->nphilo];
		}
		p[i].in = in;
		i++;
	}
}
