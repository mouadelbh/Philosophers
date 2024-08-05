/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 03:50:52 by mel-bouh          #+#    #+#             */
/*   Updated: 2024/08/05 10:07:37 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_full(t_philo *p, t_inst *in)
{
	int	i;

	i = 0;
	while (i < in->nphilo)
	{
		pthread_mutex_lock(p[i].meal_lock);
		if (p[i].full == 1)
		{
			in->full++;
			p[i].full = 0;
		}
		pthread_mutex_unlock(p[i].meal_lock);
		if (in->full == in->nphilo)
		{
			pthread_mutex_lock(&in->death_lock);
			in->death = 1;
			pthread_mutex_unlock(&in->death_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	end_death(t_philo *p, t_inst *in)
{
	int		i;
	size_t	tmp;

	i = 0;
	while (i < in->nphilo)
	{
		pthread_mutex_lock(p[i].meal_lock);
		tmp = get_current_time() - p[i].lastmeal;
		if (tmp >= in->tdie && p[i].eating == 0)
		{
			pthread_mutex_unlock(p[i].meal_lock);
			pthread_mutex_lock(&in->death_lock);
			in->death = 1;
			pthread_mutex_unlock(&in->death_lock);
			return (1);
		}
		pthread_mutex_unlock(p[i].meal_lock);
		i++;
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_philo	*p;
	t_inst	*in;

	p = (t_philo *)arg;
	in = p->in;
	while (alive(p->in))
	{
		// if (check_full(p, in))
		// 	break ;
		if (end_death(p, in))
		{
			write_starved(p->in, p->id);
			break ;
		}
	}
	return (NULL);
}
