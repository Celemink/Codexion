/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:43:30 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/12 15:57:25 by lodazzan         ###   ########.fr       */
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

void	swap_coders(t_coder **a, t_coder **b)
{
	t_coder	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
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
