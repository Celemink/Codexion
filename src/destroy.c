/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:43:47 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/11 12:53:45 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	free_simulation(t_sim *sim)
{
	int	i;

	heap_destroy(&sim->sched_heap);
	if (sim->coders)
	{
		i = 0;
		while (i < sim->number_of_coders)
		{
			pthread_mutex_destroy(&sim->coders[i].state_mutex);
			i++;
		}
		free(sim->coders);
	}
	if (sim->dongles)
	{
		i = 0;
		while (i < sim->number_of_coders)
		{
			pthread_mutex_destroy(&sim->dongles[i].mutex);
			i++;
		}
		free(sim->dongles);
	}
}
