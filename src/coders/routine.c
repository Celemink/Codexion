/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:18:22 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/10 19:27:47 by lodazzan         ###   ########.fr       */
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
		if(take_both_dongles(coder))
		{
			compile(coder);
			if (simulation_is_over(coder->general_ref))
				break;
			if (all_coders_finished(coder->general_ref))
			{
				set_simulation_over(coder->general_ref); //creo que esto es useless
				break; //MIRAR SIMULATION.C Y BORRAR SI NO SIRVE
			}
			debug(coder); //OLD CODE ARRIBA: coder->general_ref->simulation_over = 1;
			if (simulation_is_over(coder->general_ref))
				break;
			refactor(coder);
		}
		else
			precise_sleep(1);
	}
	return (NULL);
}

