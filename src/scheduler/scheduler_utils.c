/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:47:16 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/11 14:57:39 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	has_scheduler_priority(t_coder *coder)
{
	if (coder->general_ref->scheduler == FIFO)
		return (fifo_has_priority(coder));
	if (coder->general_ref->scheduler == EDF)
		return (edf_has_priority(coder));
	return (0);
}

long	coder_deadline(t_coder *coder)
{
	return (coder->last_compilation_timer
		+ coder->general_ref->time_to_burnout);
}

void	swap_coders(t_coder **a, t_coder **b)
{
	t_coder	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	smallest_checker(int sample, t_heap *heap, int smallest)
{
	if (sample < heap->size
		&& coder_deadline(heap->coders[sample])
		< coder_deadline(heap->coders[smallest]))
		return (sample);
	return (smallest);
}
