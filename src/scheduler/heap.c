/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:43:30 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/11 13:00:11 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	heap_init(t_heap *heap, int capacity)
{
	heap->coders = malloc(sizeof(t_coder *) * capacity);
	if (!heap->coders)
	{
		heap->size = 0;
		heap->capacity = 0;
		return (1);
	}
	heap->size = 0;
	heap->capacity = capacity;
	return (0);
}

void	heap_destroy(t_heap *heap)
{
	free(heap->coders);
	heap->coders = NULL;
	heap->size = 0;
	heap->capacity = 0;
}

int	heap_push(t_heap *heap, t_coder *coder)
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

t_coder	*heap_check(t_heap *heap)
{
	if (heap->size == 0)
		return (NULL);
	return (heap->coders[0]);
}

t_coder	*heap_pop(t_heap *heap)
{
	t_coder	*result;
	int		index;
	int		smallest;

	if (heap->size == 0)
		return (NULL);
	result = heap->coders[0];
	heap->size--;
	if (heap->size == 0)
		return (result);
	heap->coders[0] = heap->coders[heap->size];
	index = 0;
	while (1)
	{
		smallest = smallest_checker(index * 2 + 1, heap, index);
		smallest = smallest_checker(index * 2 + 2, heap, smallest);
		if (smallest == index)
			break ;
		swap_coders(&heap->coders[index], &heap->coders[smallest]);
		index = smallest;
	}
	return (result);
}
