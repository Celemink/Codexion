/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:43:22 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/11 17:34:36 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*int	edf_has_priority(t_coder *coder) VALGRIND CHANGES
{
	t_sim	*sim;
	long	deadline;
	long	others_deadline;
	int		i;

	sim = coder->general_ref;
	pthread_mutex_lock(&sim->scheduler_mutex);
	deadline = coder->last_compilation_timer + sim->time_to_burnout;
	i = 0;
	while (i < sim->number_of_coders)
	{
		if (sim->coders[i].waiting_since > 0 && sim->coders[i].id != coder->id)
		{
			others_deadline = sim->coders[i].last_compilation_timer
				+ sim->time_to_burnout;
			if (others_deadline < deadline)
			{
				pthread_mutex_unlock(&sim->scheduler_mutex);
				return (0);
			}
		}
		i++;
	}
	pthread_mutex_unlock(&sim->scheduler_mutex);
	return (1);
}*/

int	edf_has_priority(t_coder *coder)
{
	t_sim	*sim;
	long	now;
	long	deadline;
	long	others_deadline;
	int		i;

	sim = coder->general_ref;
	now = time_since_start(sim);
	deadline = coder->last_compilation_timer + sim->time_to_burnout;
	pthread_mutex_lock(&sim->scheduler_mutex);
	i = 0;
	while (i < sim->number_of_coders)
	{
		if (sim->coders[i].waiting_since > 0
			&& sim->coders[i].id != coder->id)
		{
			others_deadline = sim->coders[i].last_compilation_timer
				+ sim->time_to_burnout;
			if (others_deadline < deadline && others_deadline > now)
			{
				pthread_mutex_unlock(&sim->scheduler_mutex);
				return (0);
			}
		}
		i++;
	}
	pthread_mutex_unlock(&sim->scheduler_mutex);
	return (1);
}
