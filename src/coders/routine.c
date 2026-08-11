/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:18:22 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/11 11:45:45 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*coder_routine(void *arg)
{
	t_coder	*coder;
	int			i;

	i = 0;
	coder = (t_coder *)arg;
	while (!coder->general_ref->start)
		precise_sleep(1);
	while (!simulation_is_over(coder->general_ref))
	{
		simulation_finisher(coder);
		if (!fifo_has_priority(coder))
			precise_sleep(1);
	}
	return (NULL);
}

void	simulation_finisher(t_coder *coder)
{
		if (!coder->waiting_since)
			fifo_start_waiting(coder);
		if (has_scheduler_priority(coder))
		{
			if(take_both_dongles(coder))
			{
				coder->waiting_since = 0;
				compile(coder);
				if (simulation_is_over(coder->general_ref))
					return ;
				if (all_coders_finished(coder->general_ref))
				{
					set_simulation_over(coder->general_ref);
					return ;
				}
				debug(coder);
				if (simulation_is_over(coder->general_ref))
					return ;
				refactor(coder);
			}
		}
}

/*void	simlation_finisher(t_coder *coder)
{
		if (!coder->waiting_since)
			fifo_start_waiting(coder);
		if (fifo_has_priority(coder))
		{
			if(take_both_dongles(coder))
			{
				compile(coder);
				if (simulation_is_over(coder->general_ref))
					return ;
				if (all_coders_finished(coder->general_ref))
				{
					set_simulation_over(coder->general_ref); //creo que esto es useless
					return ; //MIRAR SIMULATION.C Y BORRAR SI NO SIRVE
				}
				debug(coder); //OLD CODE ARRIBA: coder->general_ref->simulation_over = 1;
				if (simulation_is_over(coder->general_ref))
					return ;
				refactor(coder);
			}
		}
}*/
//GTP TRASH
/*void	simulation_finisher(t_coder *coder)
{
	if (!coder->waiting_since)
		fifo_start_waiting(coder);
	if (fifo_has_priority(coder))
		return ;
	if(take_both_dongles(coder))
		return ;
	coder->waiting_since = 0;
	compile(coder);
	if (simulation_is_over(coder->general_ref))
				return ;
	if (all_coders_finished(coder->general_ref))
	{
		set_simulation_over(coder->general_ref); //creo que esto es useless
		return ; //MIRAR SIMULATION.C Y BORRAR SI NO SIRVE
	}
	debug(coder); //OLD CODE ARRIBA: coder->general_ref->simulation_over = 1;
	if (simulation_is_over(coder->general_ref))
			return ;
	refactor(coder);
}*/
