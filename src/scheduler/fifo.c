/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:43:26 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/11 11:47:06 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_scheduler(t_sim *sim)
{
	sim->waiting_queue = malloc(sizeof(int) * sim->number_of_coders);
	if (!sim->waiting_queue)
		return (error("Failed to allocate scheduler queue."));
	sim->queue_size = 0;
	if (pthread_mutex_init(&sim->scheduler_mutex, NULL) != 0)
	{
		free(sim->waiting_queue);
		sim->waiting_queue = NULL;
		return (error("Failed to initialize scheduler mutex."));
	}
	return (0);
}

/*void	fifo_enqueue(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->general_ref;
	pthread_mutex_lock(&sim->scheduler_mutex);
	sim->waiting_queue[sim->queue_size] = coder->id;
	sim->queue_size++;
	pthread_mutex_unlock(&sim->scheduler_mutex);
}*/

int	fifo_has_priority(t_coder *coder)
{
	t_sim	*sim;
	int		i;
	long	waiting;

	sim = coder->general_ref;
	waiting = coder->waiting_since;
	i = 0;
	while (i < sim->number_of_coders)
	{
		if (sim->coders[i].waiting_since > 0
			&& sim->coders[i].waiting_since < waiting)
			return (0);
		i++;
	}
	return (1);
}

void	fifo_start_waiting(t_coder *coder)
{
	coder->waiting_since = time_since_start(coder->general_ref);
}
