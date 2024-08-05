/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:26:07 by mel-bouh          #+#    #+#             */
/*   Updated: 2024/08/03 11:49:31 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_philo *p, t_inst *in)
{
	int	i;

	i = 0;
	if (pthread_join(in->monitor, NULL))
	{
		set_error(in);
		return (print_error("The threads joining process has failed\n"));
	}
	while (i < in->nphilo)
	{
		if (pthread_join(p[i].th, NULL))
		{
			set_error(in);
			return (print_error("The threads joining process has failed\n"));
		}
		i++;
	}
	return (1);
}

int	destroy_mutex(t_inst *in, t_fork *m, t_fork *f)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&in->death_lock))
		return (print_error("Mutex destruction failure\n"));
	if (pthread_mutex_destroy(&in->print))
		return (print_error("Mutex destruction failure\n"));
	while (i < in->nphilo)
	{
		if (pthread_mutex_destroy(&m[i]))
			return (print_error("Mutex destruction failure\n"));
		if (pthread_mutex_destroy(&f[i]))
			return (print_error("Mutex destruction failure\n"));
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_fork	f[250];
	t_fork	m[200];
	t_philo	p[250];
	t_inst	inst;

	if (!check_argument(ac, av))
		return (1);
	fill_instructions(&inst, ac, av);
	if (!check_instructions(&inst, ac))
		return (1);
	if (!init_mutex(f, m, &inst))
		return (1);
	fill_philos(p, m, &inst, f);
	if (!init_threads(p, &inst))
		return (destroy_mutex(&inst, m, f), 1);
	if (!join_threads(p, &inst))
		return (destroy_mutex(&inst, m, f), 1);
	destroy_mutex(&inst, m, f);
}
