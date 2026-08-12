/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:18:22 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/12 15:46:02 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	simulation_finisher(t_coder *coder)
{
	t_sim	*sim;
	
	sim = coder->general_ref;
	if (!coder->waiting_since)
		fifo_start_waiting(coder);
	if (has_scheduler_priority(coder))
	{
		if (take_both_dongles(coder))
		{
			pthread_mutex_lock(&sim->scheduler_mutex);
			coder->waiting_since = 0;
			pthread_mutex_unlock(&sim->scheduler_mutex);
			compile(coder);
			if (simulation_is_over(coder->general_ref))
				return ;
			if (get_compile_counter(coder) >= sim->number_of_compiles_required)
				return ;
			debug(coder);
			if (simulation_is_over(coder->general_ref))
				return ;
			refactor(coder);
		}
	}
}

void	*coder_routine(void *arg)
{
	t_coder		*coder;

	coder = (t_coder *)arg;
	pthread_mutex_lock(&coder->general_ref->simulation_mutex);
	while (!coder->general_ref->start)
	{
		pthread_mutex_unlock(&coder->general_ref->simulation_mutex);
		precise_sleep(1);
		pthread_mutex_lock(&coder->general_ref->simulation_mutex);
	}
	pthread_mutex_unlock(&coder->general_ref->simulation_mutex);
	while (!simulation_is_over(coder->general_ref))
	{
		if (get_compile_counter(coder)
			>= coder->general_ref->number_of_compiles_required)
			precise_sleep(1);
		else
		{
			simulation_finisher(coder);
			if (!fifo_has_priority(coder))
				precise_sleep(1);
		}
	}
	return (NULL);
}
