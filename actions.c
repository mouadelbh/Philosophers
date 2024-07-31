/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:57:53 by mel-bouh          #+#    #+#             */
/*   Updated: 2024/07/31 14:55:53 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	nap(t_philo *p)
{
	write_message("is sleeping 💤", p);
	usleep(p->in->tsleep * 1000);
}

void	think(t_philo *p)
{
	write_message("is thinking 🗿", p);
}

int	eat(t_philo *p)
{
	pthread_mutex_lock(p->lfork);
	write_message("has taken his left fork🍴", p);
	if (p->in->nphilo == 1)
	{
		usleep(p->in->tdie * 1000);
		return (pthread_mutex_unlock(p->lfork), 1);
	}
	pthread_mutex_lock(p->rfork);
	write_message("has taken his right fork🍴", p);
	update_meal(p);
	write_message("started eating🍽️", p);
	usleep(p->in->teat * 1000);
	pthread_mutex_lock(p->meal_lock);
	p->eating = 0;
	pthread_mutex_unlock(p->meal_lock);
	pthread_mutex_unlock(p->rfork);
	pthread_mutex_unlock(p->lfork);
	if (p->in->counter[p->id] == p->in->nmeals)
	{
		pthread_mutex_lock(p->meal_lock);
		p->full = 1;
		return (pthread_mutex_unlock(p->meal_lock), 1);
	}
	return (0);
}
