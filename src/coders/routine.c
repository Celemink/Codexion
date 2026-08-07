/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:18:22 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/07 15:41:48 by lodazzan         ###   ########.fr       */
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
	while (i < 5/*!coder->general_ref->simulation_over*/)  //cambiado para debuggear
	{
		if(take_both_dongles(coder))
		{
			log_action(coder, "\033[0;33mis compiling\033[0m");
			precise_sleep(100);
			release_both_dongles(coder);
			i++;
		}
		else
			precise_sleep(1);
	}
	return (NULL);
}

