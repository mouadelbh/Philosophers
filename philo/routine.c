/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 23:48:57 by mel-bouh          #+#    #+#             */
/*   Updated: 2024/08/05 10:12:02 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alive(t_inst *in)
{
	pthread_mutex_lock(&in->death_lock);
	if (in->death == 1)
		return (pthread_mutex_unlock(&in->death_lock), 0);
	pthread_mutex_unlock(&in->death_lock);
	return (1);
}

void	update_meal(t_philo *p)
{
	pthread_mutex_lock(p->meal_lock);
	p->eating = 1;
	p->lastmeal = get_current_time();
	// p->in->counter[p->id]++;
	pthread_mutex_unlock(p->meal_lock);
}

void	ft_usleep(size_t msec)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < msec);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->in->nphilo == 1)
	{
		pthread_mutex_lock(p->lfork);
		write_message("has taken his left fork", p);
		usleep(p->in->tdie * 1000);
		return (pthread_mutex_unlock(p->lfork), NULL);
	}
	if (p->id % 2 == 0)
		ft_usleep(100);
	while (alive(p->in))
	{
		if (eat(p))
			break ;
		nap(p);
		think(p);
	}
	return (NULL);
}
