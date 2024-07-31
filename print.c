/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 02:58:55 by mel-bouh          #+#    #+#             */
/*   Updated: 2024/07/31 14:56:00 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printtime(t_inst in)
{
	size_t	time_ms;

	time_ms = get_current_time() - in.start;
	printf("%s%lu⏰ %s", CYAN, time_ms, RESET);
}

void	write_full(t_inst *in)
{
	pthread_mutex_lock(&in->print);
	printtime(*in);
	printf("%s%sAll Philosophers are satisfied %s👌\n", GREEN, BOLD, RESET);
	pthread_mutex_unlock(&in->print);
}

void	write_starved(t_inst *in, int i)
{
	pthread_mutex_lock(&in->print);
	printtime(*in);
	printf("%s%sPhilo %i has died 💀%s\n", RED, BOLD, i, RESET);
	pthread_mutex_unlock(&in->print);
}

void	write_message(char *str, t_philo *p)
{
	pthread_mutex_lock(&p->in->print);
	if (alive(p->in) == 1)
	{
		printtime(*p->in);
		printf("%s%sPhilo %d%s %s\n", YELLOW, BOLD, p->id, RESET, str);
	}
	pthread_mutex_unlock(&p->in->print);
}
