/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:43:26 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/11 18:43:16 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	fifo_has_priority(t_coder *coder)
{
	t_sim	*sim;
	int		i;
	long	waiting;

	sim = coder->general_ref;
	pthread_mutex_lock(&sim->scheduler_mutex);
	waiting = coder->waiting_since;
	i = 0;
	while (i < sim->number_of_coders)
	{
		if (sim->coders[i].waiting_since > 0
			&& sim->coders[i].waiting_since < waiting)
		{
			pthread_mutex_unlock(&sim->scheduler_mutex);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&sim->scheduler_mutex);
	return (1);
}

void	fifo_start_waiting(t_coder *coder)
{
	pthread_mutex_lock(&coder->general_ref->scheduler_mutex);
	coder->waiting_since = time_since_start(coder->general_ref);
	pthread_mutex_unlock(&coder->general_ref->scheduler_mutex);
}
