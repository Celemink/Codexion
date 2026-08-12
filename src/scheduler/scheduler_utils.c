/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:47:16 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/12 15:54:12 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	build_waiting_heap(t_sim *sim)
{
	int	i;

	sim->sched_heap.size = 0;
	i = 0;
	while (i < sim->number_of_coders)
	{
		if (sim->coders[i].waiting_since > 0)
			heap_push(&sim->sched_heap, &sim->coders[i]);
		i++;
	}
}

int	has_scheduler_priority(t_coder *coder)
{
	t_sim	*sim;
	t_coder	*top;

	sim = coder->general_ref;
	pthread_mutex_lock(&sim->scheduler_mutex);
	build_waiting_heap(sim);
	top = heap_check(&sim->sched_heap);
	pthread_mutex_unlock(&sim->scheduler_mutex);
	return (top == NULL || top == coder);
}

long	coder_deadline(t_coder *coder)
{
	return (coder->last_compilation_timer
		+ coder->general_ref->time_to_burnout);
}

static long	coder_timer(t_coder *coder)
{
	if (coder->general_ref->scheduler == FIFO)
		return (coder->waiting_since);
	return (coder_deadline(coder));
}

int	smallest_checker(int sample, t_heap *heap, int smallest)
{
	if (sample < heap->size
		&& coder_timer(heap->coders[sample])
		< coder_timer(heap->coders[smallest]))
		return (sample);
	return (smallest);
}
