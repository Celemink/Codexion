/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 15:43:30 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/12 15:51:59 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	heap_push_edf(t_heap *heap, t_coder *coder)
{
	int	index;
	int	parent;

	if (heap->size >= heap->capacity)
		return (1);
	index = heap->size;
	heap->coders[index] = coder;
	heap->size++;
	while (index > 0)
	{
		parent = (index - 1) / 2;
		if (coder_deadline(heap->coders[parent])
			<= coder_deadline(heap->coders[index]))
			break ;
		swap_coders(&heap->coders[parent], &heap->coders[index]);
		index = parent;
	}
	return (0);
}

static int	heap_push_fifo(t_heap *heap, t_coder *coder)
{
	int	index;
	int	parent;

	if (heap->size >= heap->capacity)
		return (1);
	index = heap->size;
	heap->coders[index] = coder;
	heap->size++;
	while (index > 0)
	{
		parent = (index - 1) / 2;
		if (heap->coders[parent]->waiting_since
			<= heap->coders[index]->waiting_since)
			break ;
		swap_coders(&heap->coders[parent], &heap->coders[index]);
		index = parent;
	}
	return (0);
}

int	heap_push(t_heap *heap, t_coder *coder)
{
	if (coder->general_ref->scheduler == FIFO)
		return (heap_push_fifo(heap, coder));
	return (heap_push_edf(heap, coder));
}
